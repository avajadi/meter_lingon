#include "messaging.h"
#include "network.h"

WiFiClient networkClient;
void callback(char* topic, byte* payload, unsigned int length);

PubSubClient client(mqtt_server, 1883, callback, networkClient );

void mqtt_reconnect() {
	while (!client.connected()) {
		Serial.print("Attempting MQTT connection...");
		// Attempt to connect
		if (client.connect("meter_lingon")) {
			Serial.println("connected");
			// Once connected, publish an announcement...
			client.publish("h1/electricity", "connected");
		} else {
			Serial.print("failed, rc=");
			Serial.print(client.state());
			Serial.println(" try again in 5 seconds");
			// Wait 5 seconds before retrying
			delay(5000);
		}
	}
}

void callback(char* topic, byte* payload, unsigned int length) {
  // handle message arrived
}

void publish( const char * key, char * message ) {
	client.publish( key, message );
}
