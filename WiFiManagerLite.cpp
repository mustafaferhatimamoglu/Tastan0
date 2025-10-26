#include "WiFiManagerLite.h"

WiFiManagerLite::WiFiManagerLite(const char* ssid, const char* password)
    : ssid_(ssid), password_(password) {}

void WiFiManagerLite::enableSleep(bool on) {
  WiFi.setSleep(on);
}

void WiFiManagerLite::setTxPower(wifi_power_t pwr) {
  WiFi.setTxPower(pwr);
}

bool WiFiManagerLite::connect(uint8_t maxRetries) {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid_, password_);
  uint8_t tries = 0;
  while (WiFi.status() != WL_CONNECTED && tries < maxRetries) {
    delay(250);
    tries++;
  }
  return WiFi.status() == WL_CONNECTED;
}

bool WiFiManagerLite::isConnected() const {
  return WiFi.status() == WL_CONNECTED;
}

IPAddress WiFiManagerLite::localIP() const {
  return WiFi.localIP();
}

String WiFiManagerLite::localIPString() const {
  return WiFi.localIP().toString();
}

