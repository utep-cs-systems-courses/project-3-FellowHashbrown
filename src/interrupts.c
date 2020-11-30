#include <msp430.h>
#include "switches.h"
#include "led.h"
#include "stateMachine.h"
#include "buzz.h"

void __interrupt_vec(PORT2_VECTOR) Port_2()
{ 
  if (P2IFG & SWITCHES) {
    P2IFG &= ~SWITCHES;
    switch_interrupt_handler();
  }
}

void __interrupt_vec(WDT_VECTOR) WDT()
{
  song_advance();
  state_advance();
  led_update();
}
