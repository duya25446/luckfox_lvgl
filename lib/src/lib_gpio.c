#include "lib_gpio.h"

int gpio_export(int pin)
{
    char export_path[] = "/sys/class/gpio/export";
    int export_file = open(export_path, O_WRONLY);
    if (export_file == -1) {
        perror("Failed to open GPIO export file");
        return -1;
    }
    char pin_buffer[10];
    int bytes_written = snprintf(pin_buffer, sizeof(pin_buffer), "%d", pin);
    if (write(export_file, pin_buffer, bytes_written) == -1) {
        //perror("Failed to export GPIO pin");
        close(export_file);
    }
    close(export_file);
    return 1;
}
int gpio_input_init(int pin) 
{
    char direction_path[50];
    snprintf(direction_path, sizeof(direction_path), "/sys/class/gpio/gpio%d/direction", pin);
    int direction_file = open(direction_path, O_WRONLY);
    if (direction_file == -1) {
        perror("Failed to open GPIO direction file");
        return -1;
    }
    if (write(direction_file, "in", 2) == -1) {
        perror("Failed to set GPIO direction");
        close(direction_file);
        return -1;
    }
    close(direction_file);
    return 1;
}

int gpio_output_init(int pin) 
{

    char direction_path[50];
    snprintf(direction_path, sizeof(direction_path), "/sys/class/gpio/gpio%d/direction", pin);
    int direction_file = open(direction_path, O_WRONLY);
    if (direction_file == -1) {
        perror("Failed to open GPIO direction file");
        return -1;
    }
    if (write(direction_file, "out", 3) == -1) {
        perror("Failed to set GPIO direction");
        close(direction_file);
        return -1;
    }
    close(direction_file);

    return 1;
}

int gpio_output_write(int pin, int value) 
{
    char value_path[50];
    snprintf(value_path, sizeof(value_path), "/sys/class/gpio/gpio%d/value", pin);
    int value_file = open(value_path, O_WRONLY);
    if (value_file == -1) {
        perror("Failed to open GPIO value file");
        return -1;
    }
    char value_buffer[2];
    int bytes_written = snprintf(value_buffer, sizeof(value_buffer), "%d", value);
    if (write(value_file, value_buffer, bytes_written) == -1) {
        perror("Failed to write GPIO value");
        close(value_file);
        return -1;
    }
    close(value_file);

    return 1;
}

int gpio_input_read(int pin) 
{
    char value_path[50];
    snprintf(value_path, sizeof(value_path), "/sys/class/gpio/gpio%d/value", pin);
    int value_file = open(value_path, O_RDONLY);
    if (value_file == -1) {
        perror("Failed to open GPIO value file");
        return -1;
    }
    char value_buffer[10] = {0}; // Increase buffer size and initialize to 0
    if (read(value_file, value_buffer, sizeof(value_buffer) - 1) == -1) { // Leave space for null terminator
        perror("Failed to read GPIO value");
        close(value_file);
        return -1;
    }
    close(value_file);
    return atoi(value_buffer);
}


// void main(char* args)
// {
//     if(gpio_output_init(55) == -1)
//     {
//         printf("gpio_output_init error\n");
//         return;
//     }
//     else
//     {
//         while (1)
//         {
//             gpio_output_write(55, 1);
//             gpio_output_write(55, 0);
//         }
        
//     }
// }