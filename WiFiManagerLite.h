// Basit Wi-Fi yöneticisi
#pragma once

#include <Arduino.h>
#include <WiFi.h>
#include "esp_wifi.h"

class WiFiManagerLite {
public:
  WiFiManagerLite(const char* ssid, const char* password);
  void enableSleep(bool on);
  void setTxPower(wifi_power_t pwr);
  bool connect(uint8_t maxRetries = 40);
  bool isConnected() const;
  IPAddress localIP() const;
  String localIPString() const;

private:
  const char* ssid_;
  const char* password_;
};

