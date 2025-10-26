// ESP32-CAM – Minimal main: WiFi ve Telegram sınıfları ile sade akış
// Serial kullanılmaz; loglar Telegram ile iletilir.

#include "Config.h"
#include "WiFiManagerLite.h"
#include "TelegramBotLite.h"
#include "Blinker.h"

WiFiManagerLite wifiManager(WIFI_SSID, WIFI_PASSWORD);
TelegramBotLite telegram(BOT_TOKEN, CHAT_ID);
Blinker blinker(LED_PIN, true); // aktif HIGH LED

void setup() {
  blinker.begin();
  blinker.config(1000, 3); // 1s periyot, 3ms ON

  // Brownout'u azaltmak için güç/RF ayarları
  wifiManager.enableSleep(true);
#ifdef WIFI_TX_POWER_LEVEL
  wifiManager.setTxPower(WIFI_TX_POWER_LEVEL);
#endif

  delay(300);
  bool connected = wifiManager.connect(40);
  if (connected) {
    telegram.sendMessage(String("ESP32-CAM açıldı ✅ IP: ") + wifiManager.localIPString());
  } else {
    telegram.sendMessage("ESP32-CAM WiFi baglanamadi ❌");
  }
}

void loop() {
  blinker.tick();
}
