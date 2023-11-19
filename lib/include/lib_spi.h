#ifndef SPI_HELPER_H
#define SPI_HELPER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/spi/spidev.h>
#include <sys/ioctl.h>

#define SPI0 "/dev/spidev0.0"

int spi_init(char* device_path, uint8_t mode, uint8_t bits);
void auto_split_transfer(int spi_file, uint8_t* tx_buffer,size_t len);
int spi_transfer(int spi_file, uint8_t* tx_buffer, uint8_t* rx_buffer, size_t len);

#endif
