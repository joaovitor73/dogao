#include "../include/joystick.h"


void init_joystick()
{
    adc_init();        
    adc_gpio_init(VRX); 
    adc_gpio_init(VRY); 


    gpio_init(SW);             
    gpio_set_dir(SW, GPIO_IN); 
    gpio_pull_up(SW);       
}

void joystick_read_axis(uint16_t *vrx_value, uint16_t *vry_value)
{

    adc_select_input(ADC_CHANNEL_0); 
    sleep_us(2);                    
    *vrx_value = adc_read();        


    adc_select_input(ADC_CHANNEL_1); 
    sleep_us(2);                  
    *vry_value = adc_read();      
}


int value_of_the_pos_of_joystick_y(){
    uint16_t vry_value; 

    adc_select_input(0); 
    sleep_us(2); 
    vry_value = adc_read(); 
       
    
    if(vry_value < 500){
        return 1;  
    }
    
    else if(vry_value > 3500){
        return -1; 
    }
    
    else{
        return 0;  
    }
}


int read_movement_of_joystick_y(){
    uint16_t vry_value; 

    adc_select_input(0); 
    sleep_us(2); 
    vry_value = adc_read(); 
        
    
    if(vry_value < 500 || vry_value > 3500){
        return 1; 
    }else{
        return 0; 
    }
}


int value_of_the_pos_of_joystick_x(){
    uint16_t vrx_value; 

    adc_select_input(1); 
    sleep_us(2); 
    vrx_value = adc_read(); 
       
    
    if(vrx_value < 500){
        return 1;  
    }
    
    else if(vrx_value > 3500){
        return -1; 
    }
    
    else{
        return 0;  
    }
}


int read_movement_of_joystick_x(){
    uint16_t vrx_value; 

    adc_select_input(1); 
    sleep_us(2); 
    vrx_value = adc_read(); 
        
    
    if(vrx_value < 500 || vrx_value > 3500){
        return 1; 
    }else{
        return 0; 
    }
}

int read_movemente_of_joystick(){

    
    if(read_movement_of_joystick_x() == 1 || read_movement_of_joystick_y() == 1){
        return 1; 
    }else{
        return 0; 
    }
}

int read_movement_of_joystick_x_with_debounce(){
    static int last_state_x = 0; 
    int current_state = read_movement_of_joystick_x(); 

    sleep_ms(1);
    
    if(current_state != last_state_x){
        last_state_x = current_state; 
        return current_state; 
    }
    
    return 0;
}

int read_movement_of_joystick_y_with_debounce(){
    static int last_state_y = 0; 
    int current_state = read_movement_of_joystick_y(); 

    sleep_ms(1);
    
    if(current_state != last_state_y){
        last_state_y = current_state; 
        return current_state; 
    }
    
    return 0;
}

float read_percentage_of_move_x(){
    uint16_t vrx_value; 

    adc_select_input(1); 
    sleep_us(2); 
    vrx_value = adc_read(); 

    
    return (vrx_value-2047)/2047.0 * 100;
}

float read_percentage_of_move_y(){
    uint16_t vry_value; 

    adc_select_input(0); 
    sleep_us(2); 
    vry_value = adc_read(); 

    
    return (vry_value-2047)/2047.0 * 100;
}

int read_value_x(){
    uint16_t vrx_value; 

    adc_select_input(1); 
    sleep_us(2); 
    vrx_value = adc_read(); 

    return vrx_value; 
}

int read_value_y(){
    uint16_t vry_value; 

    adc_select_input(0); 
    sleep_us(2); 
    vry_value = adc_read(); 

    return vry_value; 
}
