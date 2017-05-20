#include "Arduino.h"
#include "meter_reader.h"
#include "network.h"
#include "messaging.h"

const char * mqtt_server = "192.168.1.176";
const unsigned int interv = 10;

unsigned long _last_time = 0;

void setup() {
  Serial.begin(19200);
  delay(5000);

  Serial.println("Setting up network");
  network_setup();

  Serial.println("Setting up network");
  messaging_setup( mqtt_server );

  Serial.println("Initialising meter reader");
  _last_time = millis();
  setup_meter_reader();
}

void loop() {
  delay(interv * 1000); // Send an update once a minute (interv in seconds)
  mqtt_reconnect();
  Serial.println("MQTT connected");
  unsigned long now = millis();
  Serial.println("Still alive, calculating average");
  unsigned long average = average_effect( now - _last_time );
  Serial.println("Still alive, calculating current");
  unsigned long current = current_effect();
  Serial.println("Still alive, updating measurement timestamp");
  _last_time = now;
  Serial.print( "\nAverage effect is " );
  Serial.print( average );
  Serial.println( " W" );
  Serial.printf( "Last read %i\n", _last_time );

  char effect_string[200];
  sprintf( effect_string, "{ \"averages\":{ \"%u seconds\": %lu}, \"current\":%lu}", interv, average, current );
  get_client().publish("h1/electricity", effect_string );
}
