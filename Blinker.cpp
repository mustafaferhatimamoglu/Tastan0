#include "Blinker.h"

Blinker::Blinker(uint8_t pin, bool activeHigh)
  : pin_(pin), activeHigh_(activeHigh) {}

void Blinker::begin() {
  pinMode(pin_, OUTPUT);
  digitalWrite(pin_, activeHigh_ ? LOW : HIGH);
}

void Blinker::config(uint32_t periodMs, uint32_t onMs) {
  period_ = (periodMs == 0) ? 1000 : periodMs;
  on_ = onMs;
}

void Blinker::tick() {
  if (period_ == 0) return;
  uint32_t m = millis() % period_;
  bool on = (m < on_);
  if (activeHigh_) {
    digitalWrite(pin_, on ? HIGH : LOW);
  } else {
    digitalWrite(pin_, on ? LOW : HIGH);
  }
}

