#include "network.h"
void network_setup() {
  WiFiManager wifiManager;
  wifiManager.autoConnect("MeterLingon");
}
