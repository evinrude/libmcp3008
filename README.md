libmcp3008
==========
Copyright (C) 2013 Mickey Malone     <mickey.malone@gmail.com>

This is a shared library used for accessing the mcp3008 10bit adc 
over the spi protocol.

The library will work on any linux platform such as the raspberry pi that supports spi and
has the mcp3008 attached.

Here are some of the references that were used:
<br />
<a href="http://www.adafruit.com/products/856">http://www.adafruit.com/products/856
</a>
<br />
<a href="http://www.raspberry-projects.com/pi/programming-in-c/spi/using-the-spi-interface">
http://www.raspberry-projects.com/pi/programming-in-c/spi/using-the-spi-interface</a>
<br />
<h3>How to use the library</h3>
<b>run "make"</b><br />
<b>run "sudo make install"</b><br />
<b>use the library</b>
```c
/** sample.c **/
#include "libmcp3008.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
int main()
{
  /** no error checking here, just a quick example **/
  uint16_t a2dval;
  int spi_fd = mcp3008_spidev_open("/dev/spidev0.0");
  
  // where to store the result, the file descriptor, mcp3008 channel, and single/differential
  mcp3008_read(&a2dval, spi_fd, CH0, 1);
  
  // print the result
  printf("%d\n", a2dval);
  
  exit(0);
}
```
<b>compile "gcc -lmcp3008 -o sample sample.c"</b>
<br><i>ensure the MCP3008 IC is on the spi bus</i>
<br /><b> run "./sample"</b>



