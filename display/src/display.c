#include "../include/display.h"

struct render_area frame_area = {
    start_column : 0,
    end_column : ssd1306_width - 1,
    start_page : 0,
    end_page : ssd1306_n_pages - 1
};

uint8_t ssd[ssd1306_buffer_length];

void dpRestart(){
    calculate_render_area_buffer_length(&frame_area);

    memset(ssd, 0, ssd1306_buffer_length);
    render_on_display(ssd, &frame_area);
}

void dpInit(){
    i2c_init(i2c1, ssd1306_i2c_clock * 1000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    ssd1306_init();
    dpRestart();
}

void dpWrite(char *mensage, int x, int y) {
    dpRestart();
    ssd1306_draw_string(ssd, x, y, mensage); 
    render_on_display(ssd, &frame_area);   // Renderiza o buffer na tela
}
