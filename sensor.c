#include "sensor.h"       // Include sensor header for function declarations
#include "adc.h"               // Include ADC functions

char str[4];

uint16_t get_speed() {
    unsigned short adc_val;
    unsigned short speed;

    adc_val = read_adc(CHANNEL4);
    if (adc_val > 1000)
        speed = 100;
    else
        speed = ((unsigned long) adc_val * 100) / 1023;
    
    str[0] = (speed / 100 ) % 10 + '0';
    str[1] = (speed / 10 ) % 10 + '0';
    str[2] = (speed % 10 ) + '0';
    str[3] = '\0';

    return speed;
}

unsigned char get_gear_pos()
{
    static char str[8] = "RN12345C"; 
    static unsigned char index = 1; 
    unsigned char key = read_digital_keypad(STATE_CHANGE);
    
    if(key == COLLISION)
    {
        index = 7;
    }
    else if(index == 7 && (key == GEAR_UP || key == GEAR_DOWN))
    {
        index = 1;
    }
    else if (key == GEAR_UP)
    {
        if (index < 6)                     // Increment gear up to '5'
        {
            index++;
        }
    }
    else if (key == GEAR_DOWN)
    {
        if (index > 0)                     // Decrement gear down to 'R'
        {
            index--;
        }
    }
    return str[index]; 
}