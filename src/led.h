#ifndef led_included
#define led_included

#include <msp430.h>

#define RED BIT0
#define GREEN BIT6
#define LEDS (BIT0 | BIT6)

void led_init();
void led_update();
void dim_75();
void dim_50();
void dim_25();
void binary_led();
void toggle_off();

extern unsigned char leds_changed, green_led_state, red_led_state;

char led_changed, red_on, green_on;

#endif
