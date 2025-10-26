// Basit millis() tabanlı LED blinker
#pragma once

#include <Arduino.h>

class Blinker {
public:
  Blinker(uint8_t pin, bool activeHigh = true);
  void begin();
  void config(uint32_t periodMs, uint32_t onMs);
  void tick();

private:
  uint8_t pin_;
  bool activeHigh_;
  uint32_t period_ = 1000;
  uint32_t on_ = 3;
};

