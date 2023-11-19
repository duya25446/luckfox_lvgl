#ifndef LIB_UART_H
#define LIB_UART_H 1


#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>

extern unsigned char uart_rxbuffer[1024];

int handle_error(int uart0_filestream, const char* error_message);
int uart_init(int port_num, int speed);
int uart_transmit(int uart0_filestream, unsigned char* data, int length);
int uart_receive(int uart0_filestream, unsigned char* data, int length);
void uart_rx_task(int uart0_filestream);
void uart_tx_task(int uart0_filestream);
pthread_t create_uart_rx_task(int uart0_filestream);
pthread_t create_uart_tx_task(int uart0_filestream);

#ifdef __cplusplus
}
#endif

#endif /* UART_H */
