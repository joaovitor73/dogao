#include <stdio.h>
#include "pico/stdlib.h"
#include "neo/include/neopixel.h"
#include "display/include/display.h"
#include "buzzer/include/buzzer.h"
int main()
{
    stdio_init_all();
    npInit();
    dpInit();
    pwm_init_buzzer();
    uint cont = 0;
    char text_buffer[5];
    while (true) {
        npSetLED(cont,0,0,240);
        npSetLED(cont+1,0,240,0);
        npSetLED(cont+2,240,0,0);
        sprintf(text_buffer, "%u", cont); 
        dpWrite(text_buffer, 60, 25);
        npWrite();
        beep(1000);
        sleep_ms(100);
        npClearRange(cont, cont+2);
        sleep_ms(100);
        dpRestart();
        cont++;
        if(cont == 26) cont = 0;
    }
}
