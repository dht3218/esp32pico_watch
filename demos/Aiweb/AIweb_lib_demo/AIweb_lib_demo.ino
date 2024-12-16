#include "AisassistantWeb.h"
#include <WiFi.h>
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  microphoneSetup();
  CHATsetup();

  // Connect to WiFi
  // WiFi.begin("dht", "12345678");
  // while (WiFi.status() != WL_CONNECTED) {
  //   delay(1000);
  //   Serial.println("Connecting to WiFi...");
  // }
  // Serial.println("Connected to WiFi");
}
extern String label;
void loop() {
//   //Serial.println(label);
//   const char* a = "";
//   a = STT_input_method();
//   Serial.print(":");
//   Serial.println(a);
//   delay(2000);
}
