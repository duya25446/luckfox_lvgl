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
static void btn_event_cbb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * btn = lv_event_get_target(e);
    if(code == LV_EVENT_CLICKED) {
        static uint8_t cnt = 0;
        cnt++;

        /*Get the first child of the button which is the label and change its text*/
        lv_obj_t * label = lv_obj_get_child(btn, 0);
        lv_label_set_text_fmt(label, "Button: %d", cnt);
    }
}

void lv_example_get_started_122(void)
{
    lv_obj_t * btn = lv_button_create(lv_screen_active());     /*Add a button the current screen*/
    lv_obj_set_pos(btn, 10, 10);                            /*Set its position*/
    lv_obj_set_size(btn, 120, 50);                          /*Set its size*/
    lv_obj_add_event(btn, btn_event_cbb, LV_EVENT_ALL, NULL);           /*Assign a callback to the button*/

    lv_obj_t * label = lv_label_create(btn);          /*Add a label to the button*/
    lv_label_set_text(label, "Button");                     /*Set the labels text*/
    lv_obj_center(label);
}

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

void main(char* args)
{
    pthread_t thread_tick;

    lv_init();

    lv_port_disp_init();

    //LVGL_CentralButton("Hello lvgl!");

    pthread_create(&thread_tick, NULL, (void*)run_tick, NULL);
    lv_example_get_started_122();
    while (1)
    {

        usleep(10000);
        lv_timer_handler();
        printf("tick:%d\n",lv_tick_get());
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