#include <stdio.h>
#include "pico/stdlib.h"
#include "neo/include/neopixel.h"
#include "display/include/display.h"
#include "buzzer/include/buzzer.h"
#include "FreeRTOS.h"
#include "task.h"
#include "joystick/include/joystick.h"
#include "button/include/button.h"
#include "rede/mqtt/include/mqtt.h"
#include "rede/wifi/include/wifi.h"
#include "led/include/led.h"

uint cont = 0;
char text_buffer[5];
uint16_t vrx_value, vry_value;
bool flag = true, pressedValue = false;
uint npOne[] = {0,0,240};
uint npTwo[] = {0,240,0};
uint npTree[] = {240,0,0};
void vNpTask(){
    while(true){
        npSetLED(cont,npOne[0], npOne[1],npOne[2]);
        npSetLED(cont+1,npTwo[0], npTwo[1], npTwo[2]);
        npSetLED(cont+2,npTree[0], npTree[1], npTree[2]);
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
        if(!pressedValue)
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

void vButtonTask(){
    while(true){
        if(pressedValue){
            npOne[0] = 240;
            npOne[1] = 0;
            npOne[2] = 0;
            npTree[0] = 0;
            npTree[1] = 0;
            npTree[2] = 240;
            npClear();
        }else{
            npOne[0] = 0;
            npOne[1] = 0;
            npOne[2] = 240;
            npTree[0] = 240;
            npTree[1] = 0;
            npTree[2] = 0;
            npClear();
        }
        vTaskDelay(250);
    }
}

void vSendValueCont(){
    while(true){
        mqtt_comm_publish("cont/value", text_buffer, strlen(text_buffer));
        vTaskDelay(500);
    }
}


int main()
{
    stdio_init_all();
    init_led_pwm();
    npInit();
    dpInit();
    pwm_init_buzzer();
    init_joystick();
    init_buttons(&pressedValue);
    onRed();
    connect_to_wifi("ssid", "password");
    mqtt_setup("bitdog2", "host", "aluno", "senha123");
    ofRed();
    xTaskCreate(vNpTask, "Np task", 128, NULL, 1, NULL);
    xTaskCreate(vDpTask, "Dp task", 128, NULL, 1, NULL);
    xTaskCreate(vBuzzerTask, "Buzzer task", 128, NULL, 1, NULL);
    xTaskCreate(vContTask, "Cont task", 128, NULL, 1, NULL);
    xTaskCreate(vJoystickTask, "Joystick task", 256, NULL, 1, NULL);
    xTaskCreate(vButtonTask, "Button task", 128, NULL, 1, NULL);
    xTaskCreate(vSendValueCont, "Send value cont", 528, NULL, 1, NULL);
    vTaskStartScheduler();
    while (true) {
        
    }
}
