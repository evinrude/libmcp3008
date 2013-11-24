/**
 *
 * libmcp3008
 * Copyright (C) 2013 Mickey Malone     <mickey.malone@gmail.com>
 *
 * This is the Shared Library used for accessing the mcp3008 10bit adc 
 * over the spi protocol.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 **/
#ifndef LIBMCP3008_C
	#define LIBMCP3008_C
#endif

#include "libmcp3008.h"
#include <errno.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

spi_settings SPI_SETTINGS = {
	1000000,      //clock speed
	0,            //us_delay
	8,            //read bits per word
	SPI_MODE_0,   //spi read mode
	0             //cs change
};

void __libmcp3008init(void);

void __libmcp3008destroy(void);

int mcp3008_spidev_open(char *spi_device)
{
	int spi_fd;

	//open the device
	if((spi_fd = open(spi_device, O_RDWR)) < 0)
	{
		return errno;
	}
	
	//set spi write mode
	if(ioctl(spi_fd, SPI_IOC_WR_MODE, &SPI_SETTINGS.spi_mode) < 0)
	{
		return errno;
	}

	//set spi read mode
	if(ioctl(spi_fd, SPI_IOC_RD_MODE, &SPI_SETTINGS.spi_mode) < 0)
	{
		return errno;
	}

	//set spi write bits per word
	if(ioctl(spi_fd, SPI_IOC_WR_BITS_PER_WORD, &SPI_SETTINGS.spi_bits_per_word) < 0)
	{
		return errno;
	}

	//set spi read bits per word
	if(ioctl(spi_fd, SPI_IOC_RD_BITS_PER_WORD, &SPI_SETTINGS.spi_bits_per_word) < 0)
	{
		return errno;
	}
    
	//set spi write clock speed
	if(ioctl(spi_fd, SPI_IOC_WR_MAX_SPEED_HZ, &SPI_SETTINGS.spi_clk_speed) < 0)
	{
		return errno;
	}

	//set spi read clock speed
	if(ioctl(spi_fd, SPI_IOC_WR_MAX_SPEED_HZ, &SPI_SETTINGS.spi_clk_speed) < 0)
	{
		return errno;
	}

	return spi_fd;
}

int mcp3008_spidev_close(int spi_fd)
{
	//open the device
	return close(spi_fd);
}

spi_settings mcp3008_create_spi_settings(int spi_clk_speed, 
                                         int spi_delay_us, 
                                         int spi_bits_per_word, 
                                         int spi_read_mode, 
                                         int spi_cs_change)
{
	spi_settings settings = { spi_clk_speed, 
                                  spi_delay_us, 
                                  spi_bits_per_word, 
                                  spi_read_mode, 
                                  spi_cs_change };
	return settings;
}

void mcp3008_use_settings(spi_settings *settings)
{
	SPI_SETTINGS = *settings;
}

int mcp3008_read(int16_t *tenbitreading, int spi_fd, int mcp3008_channel, int single)
{
	unsigned char data[3];
	
	if(single < 0 || single > 1)
	{
		errno = EINVAL;
		return errno;
	}

	data[0] = 0b00000001; //start bit
	data[1] = ((single) << 7) | ((mcp3008_channel) << 4); //single or diff, channel info moved to msb
	data[2] = 0b00000000; //don't care

	if(__send_receive_bytes(spi_fd, data, sizeof(data)) < 0)
	{
		return errno;
	}

	*tenbitreading = (int16_t) (0b00000011 & data[1]) << 8 | data[2]; //bits 0 - 9 contain the 10 bit conversion

	return 0;
}

int __send_receive_bytes(int spi_fd,
                         unsigned char *data,
                         int length)
{
	int i;
	struct spi_ioc_transfer spi[length];

	for(i = 0; i < length; i++)
	{
		spi[i] = __create_spi_ioc_transfer((unsigned long)(data + i),(unsigned long)(data + i), (sizeof(*(data + i)))); 
	}
	
	if(!spi_fd)
	{
		errno = EINVAL;
		return errno;
	}

	return ioctl(spi_fd, SPI_IOC_MESSAGE(length), &spi);
}

struct spi_ioc_transfer __create_spi_ioc_transfer(unsigned long tx_buf,
                                                  unsigned long rx_buf,
                                                  int length)
{
	struct spi_ioc_transfer spi;
	spi.tx_buf = tx_buf;
	spi.rx_buf = rx_buf;
	spi.len = length;
	spi.delay_usecs = SPI_SETTINGS.spi_delay_us;
	spi.speed_hz = SPI_SETTINGS.spi_clk_speed;
	spi.bits_per_word = SPI_SETTINGS.spi_bits_per_word;
	spi.cs_change = SPI_SETTINGS.spi_cs_change;

	return spi;
}
