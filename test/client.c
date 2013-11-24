/**
 *
 * libmcp3008
 * Copyright (C) 2013 Mickey Malone     <mickey.malone@gmail.com>
 *
 * Sample client using libmcp3008
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
#define SPI_DEVICE "/dev/spidev0.0"

#include "libmcp3008.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

int spi_fd;

void sighandler(int signal)
{
	mcp3008_spidev_close(spi_fd);
	exit(0);
}

int main()
{
	int16_t a2dval;

	spi_fd = mcp3008_spidev_open(SPI_DEVICE);
	if(spi_fd < 0)
	{
		fprintf(stderr, "Unable to open spi device [%s]: %s\n", SPI_DEVICE, strerror(errno));
		exit(-1);
	}

	while(1)
	{
		if(mcp3008_read(&a2dval, spi_fd, CH0, 1) < 0)
		{
			fprintf(stderr, "Unable to read adc value: %s\n", strerror(errno));
			exit(-1);
		}
		
		printf("\b");
		printf("\b");
		printf("\b");
		printf("\b");
		printf("%4d", a2dval);

	}

	exit(0);
}
