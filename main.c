#include <xc.h>
#define _XTAL_FREQ 20000000
#include "adc.h"
#include "sensor.h"
#include "msg.h"

void init_config() {
    init_adc();
    init_digital_keypad();
    init_can();
}

void main(void) {

    init_config();
    while (1) {
        unsigned short int speed = get_speed();
        can_transmit(SPEED_MSG_ID, (uint8_t *) & speed, 3);
        __delay_ms(100); // Delay to avoid flooding the bus

        unsigned char gear = get_gear_pos();
        can_transmit(GEAR_MSG_ID, &gear, 1); // Transmit gear over CAN bus
        __delay_ms(100); // Delay before next loop iteration
    }
    return;
}