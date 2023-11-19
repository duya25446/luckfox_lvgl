#include "lib_uart.h"


unsigned char uart_rxbuffer[1024];


int handle_error(int uart0_filestream, const char* error_message) {
    perror(error_message);
    //close(uart0_filestream);
    return -1;
}

int uart_init(int port_num, int speed) {
    char port[20];
    sprintf(port, "/dev/ttyS%d", port_num);
    int uart0_filestream = open(port, O_RDWR | O_NOCTTY | O_NDELAY);
    if (uart0_filestream == -1) {
        return handle_error(uart0_filestream, "Failed to open UART");
    }
    
    struct termios options;
    memset(&options, 0, sizeof(options));  // 清空 options 结构体
    
    if (tcgetattr(uart0_filestream, &options) != 0) {
        return handle_error(uart0_filestream, "Failed to get attributes");
    }
    
    cfsetospeed(&options, speed);
    cfsetispeed(&options, speed);

    options.c_cflag &= ~(PARENB | CSTOPB | CSIZE);  // 清除奇偶校验、停止位和数据位设置
    options.c_cflag |= CS8;  // 设置为8位数据位
    options.c_iflag = IGNPAR;  // 忽略奇偶校验错误的输入字符
    options.c_oflag = 0;  // 输出模式设置为默认
    options.c_lflag = 0;  // 非规范模式

    if (tcsetattr(uart0_filestream, TCSANOW, &options) != 0) {
        return handle_error(uart0_filestream, "Failed to set attributes");
    }

    tcflush(uart0_filestream, TCIOFLUSH);  // 清空输入输出缓冲区
    return uart0_filestream;
}



int uart_transmit(int uart0_filestream, unsigned char* data, int length)
{
    int count = write(uart0_filestream, data, length);
    if (count < 0) {
        return handle_error(uart0_filestream, "UART TX error");
    }
    return count;
}



int uart_receive(int uart0_filestream,unsigned char* data, int length)
{
    int count = read(uart0_filestream, data, length);
    if (count < 0) {
        return handle_error(uart0_filestream, "UART RX error");
    }
    return count;
}

void uart_rx_task(int uart0_filestream)
{
    int count = 0;
    while (1)
    {
        count = read(uart0_filestream, (void*)uart_rxbuffer, 1024);
        if (count > 0)
        {
            printf("RX: %s\n", uart_rxbuffer);
        }
        usleep(10);
    }
}

void uart_tx_task(int uart0_filestream)
{
    int count = 0;
    unsigned char* data = "Hello World!";
    while (1)
    {
        count = write(uart0_filestream, data, strlen(data));
        if (count > 0)
        {
            printf("TX: %s\n", data);
        }
        usleep(1000000);
    }
}

pthread_t create_uart_rx_task(int uart0_filestream)
{
    pthread_t thread_uart_rx;
    pthread_create(&thread_uart_rx, NULL, (void*)uart_rx_task, (void*)uart0_filestream);
    return thread_uart_rx;
}

pthread_t create_uart_tx_task(int uart0_filestream)
{
    pthread_t thread_uart_tx;
    pthread_create(&thread_uart_tx, NULL, (void*)uart_tx_task, (void*)uart0_filestream);
    return thread_uart_tx;
}

//demo：
// void main(char* args)
// {
//     int uart0_filestream = uart_init(3, B921600);
//     unsigned char* data = "Hello World!";
//     while (1)
//     {
//         uart_transmit(uart0_filestream, data, strlen(data));
//         sleep(1);
//         //usleep(1);  // 1 毫秒
//     }
//     close(uart0_filestream);
// }