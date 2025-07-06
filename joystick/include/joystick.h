#ifndef JOYSTICK_H
#define JOYSTICK_H

#include "pico/stdlib.h"
#include "hardware/adc.h"

#define VRX 26
#define VRY 27
#define ADC_CHANNEL_0 0
#define ADC_CHANNEL_1 1
#define SW 28

void init_joystick();
void joystick_read_axis(uint16_t *vrx_value, uint16_t *vry_value); 

// Função que retorna a posição do joystick no eixo Y
int value_of_the_pos_of_joystick_y();

// Função que detecta se houve movimento no joystick no eixo Y
int read_movement_of_joystick_y();

// Função que retorna a posição do joystick no eixo X
int read_movement_of_joystick_x_with_debounce();

// Função que detecta se houve movimento no joystick no eixo Y
int read_movement_of_joystick_y_with_debounce();

// Função que retorna a posição do joystick no eixo X
int read_movemente_of_joystick();

// Função que retorna a porcentagem da posição do joystick no eixo Y
float read_percentage_of_move_y();

// Função que retorna a posição do joystick no eixo X
int value_of_the_pos_of_joystick_x();

// Função que detecta se houve movimento no joystick no eixo X
int read_movement_of_joystick_x();

// Função que retorna a porcentagem da posição do joystick no eixo X
float read_percentage_of_move_x();

// Função que lê o valor do eixo X do joystick
int read_value_x();

// Função que lê o valor do eixo Y do joystick
int read_value_y();
#endif