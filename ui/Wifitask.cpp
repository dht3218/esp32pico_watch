
#include "Wifitask.h"
#include <WiFi.h>

int Wificonnect(const char* ssid, const char* password) {
  WiFi.begin(ssid, password);
  int wificnt = 0;
  while (WiFi.status() != WL_CONNECTED && wificnt < 10) {
    wificnt++;
    vTaskDelay(500);
    Serial.println("Connecting to WiFi...");
  }
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Connected to WiFi");
    return 1;
  } else {
    Serial.println("Connecting failed");
    return 0;
  }
}
int Wificheck() {

  if (WiFi.status() != WL_CONNECTED) return 0;
  else return 1;
}
void Wificlose() {
  WiFi.mode(WIFI_OFF);
  //WiFi.disconnect();
}