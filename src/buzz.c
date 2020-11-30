#include <msp430.h>
#include "buzz.h"
#include "notes.h"
#include "libTimer.h"
#include "switches.h"

static short song1Counter = 0;
static short song2Counter = 0;
static short song3Counter = 0;

// Fur Elise
static int song1Notes[] = {
  E4, D4sharp, E4, D4sharp, E4,
  B3, D4, C4, A3, A3, A3,
  C3, E3, A3, B3, B3, B3,
  E3, A3, B3, C4, C4, C4, E3
};
static short song1Length = 24;
static short song1Index = 0;

// In The Hall of The Mountain King
static int song2Notes[] = {
  A3, B3, C4, D4,
  E4, C4, E4, 0,
  D4sharp, B3, D4sharp, 0,
  D4, A3sharp, D4, 0,
  A3, B3, C4, D4,
  E4, C4, E4, A4,
  G4, E4, C4, E4,
  G4, G4, G4, 0
};
static short song2Length = 32;
static short song2Index = 0;

// Song 3 - Never Gonna Give You Up
static int song3Notes[] = {
  A3, B3, D4, B3,
  F4sharp, 0, F4sharp, 0, E4, E4,
  A3, B3, D4, B3,
  E4, 0, E4, 0, D4, D4, C4sharp, B3, 0,
  A3, B3, D4, B3,
  D4, D4, E4, C4sharp, C4sharp, 0, A3, 0, A3, E4, E4, D4, D4, 0
};
static short song3Length = 41;
static short song3Index = 0;

void buzzer_init()
{
  timerAUpmode();
  P2SEL2 &= ~(BIT6 | BIT7);
  P2SEL &= ~BIT7;
  P2SEL |= BIT6;
  P2DIR = BIT6;
}

void buzzer_set_period(short cycles)
{
  cycles = 2000000 / cycles;
  CCR0 = cycles;
  CCR1 = cycles >> 1;
}

void song_1()
{
  switch (song1Counter) {
  case 0:
    buzzer_set_period(song1Notes[song1Index]);
    song1Counter++;
    break;
  case 1:
    buzzer_set_period(song1Notes[song1Index]);
    if (++song1Index == song1Length) {
      song1Index = 0;
    }
    song1Counter = 0;
    break;
  }
}

void song_2()
{
  switch (song2Counter) {
  case 0:
    buzzer_set_period(song2Notes[song2Index]);
    song2Counter++;
    break;
  case 1:
    buzzer_set_period(song2Notes[song2Index]);
    if (++song2Index == song2Length) {
      song2Index = 0;
    }
    song2Counter = 0;
    break;
  }
}

void song_3()
{
  switch (song3Counter) {
  case 0:
    buzzer_set_period(song3Notes[song3Index]);
    song3Counter++;
    break;
  case 1:
    buzzer_set_period(song3Notes[song3Index]);
    if (++song3Index == song3Length) {
      song3Index = 0;
    }
    song3Counter = 0;
    break;
  }
}

void stop()
{
  buzzer_set_period(0);
}
