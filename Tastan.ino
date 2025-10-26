// ESP32-CAM (AI Thinker) – WiFi'ye bağlanıp açılışta Telegram'a mesaj gönderir
// Arduino IDE (ESP32 core) ile derleyin. Seri Hız: 115200

#include <WiFi.h>
#include <WiFiClientSecure.h>

// Wi-Fi bilgileri
const char* WIFI_SSID     = "TurkTelekom_TPBA52_2.4GHz";      // <-- düzenleyin
const char* WIFI_PASSWORD = "hbJ39MkCMJa9";  // <-- düzenleyin

// Telegram bot bilgileri
// BOT_TOKEN: BotFather'dan (örn: 123456789:AA...)
// CHAT_ID: Mesajı alacak kişi/grup chat_id'si (örn: 123456789)
const char* BOT_TOKEN = "8323126146:AAGcQUHIvtDSvo4Y3o9ASztQAMT18pQLHWQ";  // <-- düzenleyin
const char* CHAT_ID   = "6069420562";    // <-- düzenleyin

const char* TELEGRAM_HOST = "api.telegram.org";
const int   TELEGRAM_PORT = 443;

// Basit URL-encode (UTF-8 baytları %HH olarak kodlar)
String urlEncode(const String& src) {
  String out;
  const char* hex = "0123456789ABCDEF";
  for (size_t i = 0; i < src.length(); i++) {
    uint8_t c = (uint8_t)src[i];
    if ((c >= 'a' && c <= 'z') ||
        (c >= 'A' && c <= 'Z') ||
        (c >= '0' && c <= '9') ||
        c == '-' || c == '_' || c == '.' || c == '~') {
      out += (char)c;
    } else if (c == ' ') {
      out += '+';
    } else {
      out += '%';
      out += hex[(c >> 4) & 0xF];
      out += hex[c & 0xF];
    }
  }
  return out;
}

bool sendTelegramMessage(const String& message) {
  WiFiClientSecure client;
  client.setInsecure(); // Sertifika doğrulamasını kapat (geliştirme için pratik)

  if (!client.connect(TELEGRAM_HOST, TELEGRAM_PORT)) {
    Serial.println("Telegram sunucusuna baglanamadi");
    return false;
  }

  String path = "/bot" + String(BOT_TOKEN) + "/sendMessage";
  String body = "chat_id=" + String(CHAT_ID) + "&text=" + urlEncode(message);

  String req;
  req  = "POST " + path + " HTTP/1.1\r\n";
  req += "Host: " + String(TELEGRAM_HOST) + "\r\n";
  req += "User-Agent: ESP32-CAM\r\n";
  req += "Content-Type: application/x-www-form-urlencoded\r\n";
  req += "Connection: close\r\n";
  req += "Content-Length: " + String(body.length()) + "\r\n\r\n";
  req += body;

  client.print(req);

  // Basit yanit kontrolu (5 sn bekle)
  unsigned long tStart = millis();
  while (client.connected() && !client.available() && millis() - tStart < 5000) {
    delay(10);
  }
  String statusLine = client.readStringUntil('\n');
  Serial.print("HTTP Status: ");
  Serial.println(statusLine);

  bool ok = statusLine.indexOf("200 OK") > 0;

  // Geri kalanını tüket
  while (client.available()) client.read();
  client.stop();
  return ok;
}

void connectWiFi(uint8_t maxRetries = 40) {
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("WiFi baglantisi: ");
  uint8_t tries = 0;
  while (WiFi.status() != WL_CONNECTED && tries < maxRetries) {
    delay(250);
    Serial.print('.');
    tries++;
  }
  Serial.println();
  if (WiFi.status() == WL_CONNECTED) {
    Serial.print("Baglandi, IP: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("WiFi baglantisi basarisiz");
  }
}

void setup() {
  Serial.begin(115200);
  delay(300);

  connectWiFi();

  if (WiFi.status() == WL_CONNECTED) {
    String msg = "ESP32-CAM açıldı ✅"; // Türkçe karakterler URL-encode ile gönderilir
    bool sent = false;

    // 3 denemeye kadar gönder
    for (int i = 0; i < 3 && !sent; i++) {
      sent = sendTelegramMessage(msg);
      if (!sent) {
        Serial.println("Gonderim basarisiz, tekrar denenecek...");
        delay(1500);
      }
    }

    if (sent) {
      Serial.println("Telegram mesaji gonderildi.");
    } else {
      Serial.println("Telegram mesaji gonderilemedi.");
    }
  }
}

void loop() {
  // Gerekirse derin uykuya alin: esp_deep_sleep_start();
  delay(1000);
}

