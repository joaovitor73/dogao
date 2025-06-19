#include <stdio.h>
#include "pico/stdlib.h"
#include "neo/include/neopixel.h"
#include "display/include/display.h"
#include "buzzer/include/buzzer.h"
#include "FreeRTOS.h"
#include "task.h"
#include "joystick/include/joystick.h"

uint cont = 0;
char text_buffer[5];
uint16_t vrx_value, vry_value;
bool flag = true;
void vNpTask(){
    while(true){
        npSetLED(cont,0,0,240);
        npSetLED(cont+1,0,240,0);
        npSetLED(cont+2,240,0,0);
        npWrite();
        vTaskDelay(250);
        npClear();
        vTaskDelay(250);
    }
}

void vDpTask(){
     while(true){
        sprintf(text_buffer, "%u", cont); 
        dpWrite(text_buffer, 60, 25);
        vTaskDelay(250);
        dpRestart();
    }
}

void vBuzzerTask(){
    while(true){
        beep(200);
        vTaskDelay(250);
    }
}

void vContTask(){
    while(true){
        if(flag) cont++;
        vTaskDelay(250);
        if(cont == 26) cont = 0;
        vTaskDelay(250);
    }
}

void vJoystickTask(){
    while(true){
        joystick_read_axis(&vrx_value, &vry_value);
        if (vrx_value < 300){
            if (cont > 0) cont--;
            else cont = 25;
            flag = false;
        }else if (vrx_value > 3500){
            if (cont < 25) cont++;
            else cont = 0;
            flag = false;
        }else{
            flag = true;
        }
        vTaskDelay(300);
    }
}


int main()
{
    stdio_init_all();
    npInit();
    dpInit();
    pwm_init_buzzer();
    init_joystick();


    xTaskCreate(vNpTask, "Np task", 128, NULL, 1, NULL);
    xTaskCreate(vDpTask, "Dp task", 128, NULL, 1, NULL);
    xTaskCreate(vBuzzerTask, "Buzzer task", 128, NULL, 1, NULL);
    xTaskCreate(vContTask, "Cont task", 128, NULL, 1, NULL);
    xTaskCreate(vJoystickTask, "Joystick task", 256, NULL, 1, NULL);
    vTaskStartScheduler();
    while (true) {
        
    }
}
