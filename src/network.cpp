#include "network.h"
void network_setup() {
  WiFiManager wifiManager;
  //TODO Add configuration input for id, average effect interval and mqtt_server
  wifiManager.autoConnect("MeterLingon");
}
