#include "Arduino.h"
#include "meter_reader.h"
#include "network.h"
#include "messaging.h"

const unsigned int interv = 10; //TODO Keep in EEPROM, configure in WifiManager captive portal
const char * id = "torpet"; //TODO Keep in EEPROM, configure in WifiManager captive portal

const char * payload_format = "{ \"averages\":{ \"%u seconds\": %lu}, \"current\":%lu}";
const char * key_format = "%s/electricity";
unsigned long _last_time = 0;

char _key[50];

void setup() {
  Serial.begin(19200);
  sprintf( _key, key_format, id );
  delay(5000);

  Serial.print( "MQTT root: " );
  Serial.println( _key );

  Serial.println("Setting up network");
  network_setup();

  Serial.println("Initialising meter reader");
  _last_time = millis();
  setup_meter_reader();
}

void loop() {
  delay(interv * 1000); // Send an update once a minute (interv in seconds)
  mqtt_reconnect();
  Serial.println("MQTT connected");
  unsigned long now = millis();
  unsigned long average = average_effect( now - _last_time );
  unsigned long current = current_effect();

  _last_time = now;
  Serial.print( "\nAverage effect is " );
  Serial.print( average );
  Serial.println( " W" );

  Serial.print( "\nLast read effect is " );
  Serial.print( current );
  Serial.println( " W" );

  Serial.printf( "Last read %i\n", _last_time );

  char _payload[200];
  sprintf( _payload, payload_format, interv, average, current );
  publish( _key, _payload );
}
