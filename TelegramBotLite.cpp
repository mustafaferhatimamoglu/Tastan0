#include "TelegramBotLite.h"

TelegramBotLite::TelegramBotLite(const char* token, const char* chatId)
  : token_(token), chatId_(chatId) {}

String TelegramBotLite::urlEncode(const String& src) {
  String out;
  const char* hex = "0123456789ABCDEF";
  for (size_t i = 0; i < src.length(); i++) {
    uint8_t c = (uint8_t)src[i];
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
        (c >= '0' && c <= '9') || c == '-' || c == '_' || c == '.' || c == '~') {
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

bool TelegramBotLite::sendMessage(const String& message) {
  WiFiClientSecure client;
  client.setInsecure();

  if (!client.connect(TELEGRAM_HOST, TELEGRAM_PORT)) {
    return false;
  }

  String path = "/bot" + String(token_) + "/sendMessage";
  String body = "chat_id=" + String(chatId_) + "&text=" + urlEncode(message);

  String req;
  req  = "POST " + path + " HTTP/1.1\r\n";
  req += String("Host: ") + TELEGRAM_HOST + "\r\n";
  req += "User-Agent: ESP32-CAM\r\n";
  req += "Content-Type: application/x-www-form-urlencoded\r\n";
  req += "Connection: close\r\n";
  req += "Content-Length: " + String(body.length()) + "\r\n\r\n";
  req += body;

  client.print(req);

  unsigned long tStart = millis();
  while (client.connected() && !client.available() && millis() - tStart < 5000) {
    delay(10);
  }
  String statusLine = client.readStringUntil('\n');
  bool ok = statusLine.indexOf("200 OK") > 0;

  while (client.available()) client.read();
  client.stop();
  return ok;
}

