#include <msp430.h>
#include "led.h"
#include "switches.h"

static char red[] = {0, RED}, green[] = {0, GREEN};

unsigned char red_led_state = 0;
unsigned char green_led_state = 0;

void led_init()
{
  P1DIR |= LEDS;
  led_changed = 1;
  led_update();
}

void led_update()
{
  if (led_changed) {
    char ledFlags = 0;

    ledFlags = red[red_on] | green[green_on];

    P1OUT &= (0xff ^ LEDS) | ledFlags;
    P1OUT |= ledFlags;
    led_changed = 0;
  }
}

void dim_75()
{
  switch (red_led_state) {
    case 2:
    case 3:
    case 4:
    case 5:
      red_on = 1;
      green_on = 1;
      if (++red_led_state == 6) {
        red_led_state = 0;
      }
      break;
    case 0:
    case 1:
      red_on = 0;
      green_on = 0;
      red_led_state++;
      break;
  }
  led_changed = 1;
}

void dim_50()
{
  switch (green_led_state) {
    case 0:
    case 1:
    case 2:
      green_on = 1;
      red_on = 1;
      green_led_state++;
      break;
    case 3:
    case 4:
    case 5:
      green_on = 0;
      red_on = 0;
      if (++green_led_state == 6) {
        green_led_state = 0;
      }
      break;
  }
  led_changed = 1;
}

void dim_25()
{
  switch (red_led_state) {
    case 2:
    case 3:
    case 4:
    case 5:
      red_on = 0;
      green_on = 0;
      if (++red_led_state == 6) {
        red_led_state = 0;
      }
      break;
    case 0:
    case 1:
      red_on = 1;
      green_on = 1;
      red_led_state++;
      break;
  }
  led_changed = 1;
}

void binary_led()
{
  switch (red_led_state) {
  case 0:
    red_on = 0;
    green_on = 0;
    red_led_state++;
    break;
  case 1:
    red_on = 1;
    red_led_state++;
    break;
  case 2:
    red_on = 0;
    green_on = 1;
    red_led_state++;
    break;
  case 3:
    red_on = 1;
    red_led_state = 0;
    break;
  }
}
void toggle_red()
{
  switch (red_led_state) {
  case 0: case 2:
    red_on = 1;
    if(++red_led_state == 3) {
      red_led_state = 0;
    }
    break;
  case 1: case 3:
    red_on = 0;
    red_led_state++;
    break;
  }
  led_changed = 1;
}

void toggle_green()
{
  switch (green_led_state) {
  case 0: case 1:
    green_on = 1;
    green_led_state++;
    break;
  case 2: case 3:
    green_on = 0;
    if (++green_led_state == 3) {
      green_led_state = 0;
    }
    break;
  }
  led_changed = 1;
}

void toggle_red_green()
{
  toggle_red();
  toggle_green();
  led_changed = 1;
}

void toggle_off()
{
  red_on = green_on = 0;
  led_changed = 1;
}
