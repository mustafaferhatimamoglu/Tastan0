// Basit Telegram istemcisi (HTTPS POST)
#pragma once

#include <Arduino.h>
#include <WiFiClientSecure.h>
#include "Config.h"

class TelegramBotLite {
public:
  TelegramBotLite(const char* token, const char* chatId);
  bool sendMessage(const String& message);

private:
  String urlEncode(const String& src);

  const char* token_;
  const char* chatId_;
};

