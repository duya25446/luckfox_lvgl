#include "lib_spi.h"

int spi_init(char* device_path, uint8_t mode, uint8_t bits) {
    int spi_file;
    uint8_t lsb_first = 0;

    if ((spi_file = open(device_path, O_RDWR)) < 0) {
        perror("Failed to open SPI device");
        return -1;
    }

    if (ioctl(spi_file, SPI_IOC_WR_MODE, &mode) < 0) {
        perror("Failed to set SPI mode");
        close(spi_file);
        return -1;
    }
    if (ioctl(spi_file, SPI_IOC_WR_LSB_FIRST, &lsb_first) < 0) {
        perror("Failed to set SPI mode");
        close(spi_file);
        return -1;
    }

    if (ioctl(spi_file, SPI_IOC_WR_BITS_PER_WORD, &bits) < 0) {
        perror("Failed to set SPI bits per word");
        close(spi_file);
        return -1;
    }

    return spi_file;
}

void auto_split_transfer(int spi_file, uint8_t* tx_buffer,size_t len)
{
    uint8_t *begin = tx_buffer;
	uint8_t *end = tx_buffer + len;
	while (begin < end) 
	{
        size_t len = (end - begin < 4096) ? end - begin : 4096;
        spi_transfer(spi_file,begin,NULL,len);
        begin += len;
	}
}

int spi_transfer(int spi_file, uint8_t* tx_buffer, uint8_t* rx_buffer, size_t len) {
    struct spi_ioc_transfer transfer = {
        .tx_buf = (unsigned long)tx_buffer,
        .rx_buf = (unsigned long)rx_buffer,
        .len = len,
        .delay_usecs = 0,
        .speed_hz = 50000000,
        .bits_per_word = 8,
    };

    if (ioctl(spi_file, SPI_IOC_MESSAGE(1), &transfer) < 0) {
        perror("Failed to perform SPI transfer");
        return -1;
    }

    return 0;
}

// void main(char* args)
// {
//     int spi_file = spi_init(SPI0, 0, 8);
//     if (spi_file < 0) {
//         return;
//     }

//     uint8_t tx_buffer[2] = {0x01, 0x02};
//     uint8_t rx_buffer[2] = {0x00, 0x00};
//     while(1)
//     {
//         spi_transfer(spi_file, tx_buffer, rx_buffer, 2);
//         printf("Received: %02x %02x\n", rx_buffer[0], rx_buffer[1]);
//         sleep(1);
//     }

//     close(spi_file);
// }