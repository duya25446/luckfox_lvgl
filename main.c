#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "lib_uart.h"
#include "lib_gpio.h"
#include "main.h"
#include "lcd.h"
#include "lcd_init.h"
#include "lvgl.h"

// 55 54 34 4


void LVGL_CentralButton(const char * args)
{
    lv_obj_t *btn = lv_btn_create(lv_scr_act());
    lv_obj_align(btn, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_height(btn, 30);
 
    lv_obj_t *label;
    label = lv_label_create(btn);
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
    lv_label_set_text(label, args);
 
    static lv_style_t style_btn;
    lv_style_init(&style_btn);
    lv_style_set_radius(&style_btn, 10);
    lv_style_set_border_color(&style_btn, lv_color_white());
    lv_style_set_border_opa(&style_btn, LV_OPA_30);
    lv_obj_add_style(btn, &style_btn, LV_STATE_DEFAULT);
}

void run_tick()
{
    while (1)
    {
        usleep(1000);
        lv_tick_inc(1);
    }
    
}

void run_handle()
{
    while (1)
    {
        usleep(1000);
        lv_task_handler();
    }
}

void main(char* args)
{
    pthread_t thread_tick;
    pthread_t thread_handle;

    lv_init();

    lv_port_disp_init();

    LVGL_CentralButton("Hello");

    pthread_create(&thread_tick, NULL, (void*)run_tick, NULL);
    pthread_create(&thread_handle, NULL, (void*)run_handle, NULL);

    while (1)
    {

        //printf("tick:%d\n",lv_tick_get());
        //lv_example_get_started_122();
        //printf("Hello lvgl!\n");
        //LVGL_CentralButton("Hello lvgl!");
    }
    // int uart0_filestream = uart_init(3, B921600);
    // unsigned char* data = "Hello World!";
    // create_uart_rx_task(uart0_filestream);
    // while (1)
    // {
    //     uart_transmit(uart0_filestream, data, strlen(data));
    //     sleep(1);
    //     //usleep(1);  // 1 毫秒
    // }
    // close(uart0_filestream);
}