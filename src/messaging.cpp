#include "messaging.h"
#include "network.h"

WiFiClient espClient;
PubSubClient client(espClient);

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

PubSubClient get_client() {
	return client;
}
void messaging_setup( const char * mqtt_server ) {
  client.setServer(mqtt_server, 1883);
}
