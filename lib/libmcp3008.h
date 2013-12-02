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
#ifdef __cplusplus
extern "C" {
#endif
#ifndef LIBMCP3008_H
	#define LIBMCP3008_H
#endif

#include <linux/spi/spidev.h>
#include <stdint.h>

typedef struct spi_settings {
	int spi_clk_speed;
	int spi_delay_us;
	int spi_bits_per_word;
	int spi_mode;
	int spi_cs_change;
} spi_settings;

enum mcp3008_channel {
	CH0,
	CH1,
	CH2,
	CH3,
	CH4,
	CH5,
	CH6,
	CH7
};

/** constructor **/
void __libmcp3008init(void) __attribute__ ((constructor));

/** deconstructor **/
void __libmcp3008destroy(void) __attribute__ ((destructor));

/** open the specified spi device
    returns a file descriptor to the device **/
int mcp3008_spidev_open(char *spi_device);

/** close the spi device 
    returns non zero on failure and sets errno **/
int mcp3008_spidev_close(int spi_fd);

/** create spi settings
    returns a spi_settings structure **/
spi_settings mcp3008_create_spi_settings(int spi_clk_speed,
                                         int spi_delay_us,
                                         int spi_bits_per_word,
                                         int spi_mode,
                                         int spi_cs_change);

/** apply non-default spi settings to library communication with the mcp3008
    this applies to all communications over spi for the life of the shared object**/
void mcp3008_use_settings(spi_settings *settings);

/** perform an adc read on the specified channel
    if single is 0 or false, then a diff of the previous
    reading will be performed 
    returns 0 and sets tenbitreading on success**/
int mcp3008_read(int16_t *tenbitreading, int spi_fd, int mcp3008_channel, int single);

/** write and read byte from spi device
    returns non zero on failure and sets errno **/
int __send_receive_bytes(int spi_fd,
                         unsigned char *data,
                         int length);

/** create a spi_ioc_transfer structure **/
struct spi_ioc_transfer __create_spi_ioc_transfer(unsigned long tx_buf,
                                                  unsigned long rx_buf,
                                                  int length);
#ifdef __cplusplus
}
#endif
