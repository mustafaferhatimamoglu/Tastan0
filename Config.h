// Konfigürasyon – Kimlik bilgileri ve pinler
#pragma once

#include <Arduino.h>

// Wi-Fi bilgileri (mevcut eskizden taşındı)
static const char* WIFI_SSID     = "TurkTelekom_TPBA52_2.4GHz";
static const char* WIFI_PASSWORD = "hbJ39MkCMJa9";

// Telegram bot bilgileri
static const char* BOT_TOKEN = "8323126146:AAGcQUHIvtDSvo4Y3o9ASztQAMT18pQLHWQ";
static const char* CHAT_ID   = "6069420562";

// Telegram sunucusu
#define TELEGRAM_HOST "api.telegram.org"
#define TELEGRAM_PORT 443

// LED pin (AI Thinker ESP32-CAM flaş LED'i)
#define LED_PIN 4

// İsteğe bağlı: Wi-Fi TX güç seviyesi (çekim zayıfsa yorum satırı yapın)
#define WIFI_TX_POWER_LEVEL WIFI_POWER_8_5dBm

