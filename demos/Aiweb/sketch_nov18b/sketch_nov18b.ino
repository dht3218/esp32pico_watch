#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>



// 替换为你的WiFi网络名称和密码
const char* ssid = "dht";
const char* password = "12345678";

// Spark API的URL和授权信息
const char* url = "https://spark-api-open.xf-yun.com/v1/chat/completions";
const char* authorization = "Bearer GfnukHUxljsYtRFEsEWG:PjDPcjFvHKwiOwuTkkaW";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("start");
    HTTPClient http;
    http.begin(url);
    http.addHeader("Authorization", authorization);
    http.addHeader("Content-Type", "application/json");

    String requestBody0 = R"({
    "max_tokens": 4096,
    "top_k": 4,
    "temperature": 0.5,
    "messages": [
        {
            "role": "system",
            "content": )";
    String requestBody1 = "\"你是一个智能管家 简要回答不超过20字\"";
    String requestBody2 = R"(        
            ,
            "role": "user",
            "content": "广州今天天气如何"
        }
    ],
    "model": "generalv3",
    "stream": true
})";
    String requestBody = requestBody0 + requestBody1 + requestBody2;
    int httpResponseCode = http.POST(requestBody);

    if (httpResponseCode > 0) {
      // int len = http.getSize();
      // Serial.print("len");Serial.print(len);

      Stream* stream = http.getStreamPtr();
      stream->setTimeout(200);
      String response = "";
      String responseOut = "";


      while (http.connected()) {
        //if (size) {
        // read up to 512 byte
        response = stream->readStringUntil('\n');
        // Serial.println(response);
        // Serial.println("response");
        if (response.startsWith("data: ")) {
          response = response.substring(6);
          if (response.startsWith("[DONE]")) break;
          JsonDocument doc;
          DeserializationError error = deserializeJson(doc, response);
          const char* responseString = doc["choices"][0]["delta"]["content"];  // "今天是"
          Serial.println(responseString);
          responseOut = responseOut + responseString;
        }
        // }
      }

      Serial.println(" ");
      Serial.println(responseOut);

      // if (error) {
      //   Serial.print("deserializeJson() failed: ");
      //   Serial.println(error.c_str());
      //   return;
      // }

      //Serial.println(response);



    } else {
      Serial.print("Error on sending POST: ");
      Serial.println(httpResponseCode);
    }

    http.end();
  } else {
    Serial.println("WiFi Disconnected");
  }

  // 延迟一段时间再发送下一次请求（例如每分钟一次）
  delay(5000);
}
