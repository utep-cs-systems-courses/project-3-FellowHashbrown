#include <msp430.h>
#include "libTimer.h"
#include "led.h"
#include "switches.h"
#include "stateMachine.h"
#include "buzz.h"

char switch_state_changed;

char sw1_state_down, sw2_state_down, sw3_state_down, sw4_state_down;

static char switch_update_interrupt_sense()
{
  char p2val = P2IN;
  P2IES |= (p2val & SWITCHES);
  P2IES &= (p2val & ~SWITCHES);
  return p2val;
}

void switch_init()
{
  P2REN |= SWITCHES;
  P2IE = SWITCHES;
  P2OUT |= SWITCHES;
  P2DIR &= ~SWITCHES;
  switch_update_interrupt_sense();
}

void switch_interrupt_handler()
{
  char p2val = switch_update_interrupt_sense();

  sw1_state_down = (p2val & SW1) ? 1: 0;
  sw2_state_down = (p2val & SW2) ? 1: 0;
  sw3_state_down = (p2val & SW3) ? 1: 0;
  sw4_state_down = (p2val & SW4) ? 1: 0;

  // Do fur elise and show a blinking green led
  if (!(p2val & sw1_state_down)) {
    switch_state_changed = 1;

    // Do the c scale and show a blinking red led
  } else if (!(p2val & sw2_state_down)) {
    switch_state_changed = 2;

    // Do the inverted c scale and show both leds
  } else if (!(p2val & sw3_state_down)) {
    switch_state_changed = 3;

    // Stop the song and show no leds
  } else if (!(p2val & sw4_state_down)) {
    switch_state_changed = 4;
  }
}
