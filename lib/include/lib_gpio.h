#ifndef GPIO_H
#define GPIO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int gpio_export(int pin);
int gpio_input_init(int pin);
int gpio_output_init(int pin);
int gpio_output_write(int pin, int value);
int gpio_input_read(int pin);

#endif
