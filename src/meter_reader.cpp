#include "Arduino.h"
#include "meter_reader.h"
#include <climits>
const unsigned long TIME_UNITS_PER_SECOND = 1000;

volatile unsigned long pulseCount;
volatile unsigned long lastInterval;
volatile unsigned long lastNow;

void countPulse() {
	pulseCount++;
	unsigned long now = millis();
	lastInterval = now - lastNow;
	lastNow = now;
	Serial.print('.');
}

unsigned int readPulseCount() {
	unsigned int count = pulseCount;
	pulseCount = 0;
	return count;
}

/** Calculate the current effect based on the current interval between meter pulses
 * current_effect =  1000 / PULSES_PER_KWH / current_interval
 * effect_per_pulse = 1000 / PULSES_PER_KWH
 * @current_interval in microseconds
 * @return current effect, in W
 */
unsigned long current_effect() {
	Serial.print("Last interval was ");
	Serial.print( lastInterval );
	Serial.println( "ms" );
	if( lastInterval == ULONG_MAX  ) {
		Serial.println( "NO READING YET" );
	}
	return TIME_UNITS_PER_SECOND * JOULES_PER_PULSE / lastInterval;
}

unsigned long average_effect( unsigned long current_interval ) {
	return readPulseCount() * ( JOULES_PER_PULSE ) / ( current_interval / TIME_UNITS_PER_SECOND );
}

void setup_meter_reader() {
	pulseCount = 0;
	lastInterval = ULONG_MAX;
	lastNow = millis();
	pinMode( INTERRUPT_PIN, INPUT_PULLUP );
	attachInterrupt( digitalPinToInterrupt( INTERRUPT_PIN ), countPulse, RISING );
}
