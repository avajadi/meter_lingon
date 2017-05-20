#ifndef _MESSAGING_H
#define _MESSAGING_H
#include <PubSubClient.h>

const char * mqtt_server = "192.168.1.176"; //TODO Keep in EEPROM, configure in WifiManager captive portal

void mqtt_reconnect();
void publish( const char * key, char * message );
#endif
