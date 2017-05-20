#ifndef _METER_READER_H
#define _METER_READER_H

#include "Arduino.h"

const unsigned long PULSES_PER_KWH = 500L;
const uint8_t INTERRUPT_PIN = D7;
const unsigned long KWH = 3600000L; // Joule (3600 seconds per hour, 1000 watts per kW)
const int JOULES_PER_PULSE = KWH / PULSES_PER_KWH;

unsigned long average_effect( unsigned long current_interval );
unsigned long current_effect();
//void onPulse();
void setup_meter_reader();
#endif
