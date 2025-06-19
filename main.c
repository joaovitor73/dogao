#include <stdio.h>
#include "pico/stdlib.h"
#include "neo/include/neopixel.h"


int main()
{
    stdio_init_all();
    npInit();
    npClear();
    uint cont = 0;
    while (true) {
        npSetLED(cont,0,0,240);
        npSetLED(cont+1,0,240,0);
        npSetLED(cont+2,240,0,0);
        npWrite();
        sleep_ms(100);
        npClearRange(cont, cont+2);
        sleep_ms(100);
        cont++;
        if(cont == 26) cont = 0;
    }
}
