#include <WiFi.h>
#include <SPIFFS.h>

// 定义存储文件的文件名
const char* wifi_config_file = "/wifi_config.txt";

// 定义变量存储 WiFi 信息
// 1）不填写为空时通过smartconfig流程进行配网
// 2）填写具体WiFi信息后直接根据填写的账号密码信息进行联网
const char* ssid = "";
const char* password = "";

// 设置断网重连的时间间隔
const uint32_t RECONNECT_TIMEOUT = 20000;  // 20s

void setup() {
  Serial.begin(115200);

  // 初始化 SPIFFS 文件系统
  if (!SPIFFS.begin(true)) {
    Serial.println("SPIFFS 初始化失败");
    return;
  }

  // 如果直接代码中ssid password 配置了，则直接去连接wifi
  if (ssid != NULL && password != NULL && ssid[0] != '\0' && password[0] != '\0') {
    // 尝试连接 WiFi
    connectToWifi(ssid, password, 10);
  } else {
    // 从flash中读取ssid password 后连接WiFi
    connectToWifiSSIDFromFlash();
  }
}

void loop() {
  // 定时检查 WiFi 连接状态
  if (WiFi.status() != WL_CONNECTED) {
    handleDisconnect();
  } else {
    Serial.println("连接WIFI成功");
    delay(3000);
  }
}

void connectToWifiSSIDFromFlash(void) {
  char ssidRead[32];
  char passwordRead[64];
  // 从 SPIFFS 文件中读取 WiFi 配置信息
  readCredentialsFromSPIFFS(ssidRead, passwordRead);

  if (ssidRead[0] != '\0' && passwordRead[0] != '\0') {
    Serial.print("ssid：");
    Serial.print(ssidRead);
    Serial.print(" password：");
    Serial.println(passwordRead);

    // 尝试连接 WiFi
    connectToWifi(ssidRead, passwordRead, 10);
  } else {
    // 进入 SmartConfig 模式
    startSmartConfig();
  }
}

// 尝试连接 WiFi
void connectToWifi(const char* ssid, const char* password, uint32_t maxTimeoutSec) {
  uint8_t connected = 1;
  uint32_t waitTimeMs = 0;

  WiFi.begin(ssid, password);
  Serial.print("连接WIFI：");
  Serial.println(ssid);

  // 等待连接成功
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
    waitTimeMs += 1000;

    if (waitTimeMs / 1000 > maxTimeoutSec) {
      connected = 0;
      break;
    }
  }

  if (connected) {
    // 连接成功
    Serial.println("");
    Serial.println("WIFI连接成功");
    Serial.print("IP地址：");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("WIFI连接失败");
  }
}

// 处理断网事件
void handleDisconnect() {
  // 用于记录上次重连尝试的时间
  static uint32_t firstReconnectAttempt = 0;
  // 用于记录重连的计数值
  static uint8_t reconnectCount = 0;

  Serial.println("WIFI连接断开，重新连接");

  // 检查是否需要重新进行 SmartConfig
  if (millis() - firstReconnectAttempt > RECONNECT_TIMEOUT) {
    // 置零
    reconnectCount = 0;

    Serial.println("连接失败，重新进行 SmartConfig");
    startSmartConfig();
  } else {
    if (reconnectCount++ == 1) {
      firstReconnectAttempt = millis();
    }
    connectToWifiSSIDFromFlash();
  }
}

// 从 SPIFFS 文件中读取 WiFi 配置信息
void readCredentialsFromSPIFFS(char* ssid, char* password) {
  File configFile = SPIFFS.open(wifi_config_file, "r");
  if (configFile) {
    // 读取 SSID 和密码
    configFile.readStringUntil('\n').toCharArray(ssid, 32);
    configFile.readStringUntil('\n').toCharArray(password, 64);
    configFile.close();
    Serial.println("从 SPIFFS 读取配置文件成功");
  } else {
    Serial.println("读取 SPIFFS 文件失败");
  }
}

// 将 WiFi 配置信息保存到 SPIFFS 文件
void saveCredentialsToSPIFFS(const char* ssidNew, const char* passwordNew) {
  File configFile = SPIFFS.open(wifi_config_file, "w");
  if (configFile) {
    // 写入 SSID 和密码
    configFile.print(ssidNew);
    configFile.print('\n');
    configFile.print(passwordNew);
    configFile.close();
    Serial.println("将配置信息保存到 SPIFFS 成功");
  } else {
    Serial.println("写入 SPIFFS 文件失败");
  }
}

// SmartConfig 完成处理
void smartConfigDoneHandle(void) {
  // 获取配置信息
  String ssid = WiFi.SSID();
  String password = WiFi.psk();
  char* ssidSave = (char*)&ssid[0];
  char* passwordSave = (char*)&password[0];

  Serial.println("SmartConfig 配置成功：");
  Serial.print("ssid：");
  Serial.print(ssidSave);
  Serial.print(" password：");
  Serial.println(passwordSave);

  // 保存配置信息到 SPIFFS
  saveCredentialsToSPIFFS(ssidSave, passwordSave);

  // 重新启动设备
  ESP.restart();
}

// 开始 SmartConfig 模式
void startSmartConfig() {
  // 初始化 WiFi
  WiFi.mode(WIFI_MODE_STA);
  WiFi.beginSmartConfig();

  Serial.println("请使用手机 小程序/APP 进行配置, 正在等待SmartConfig配置");

  //等待来自手机的SmartConfig数据包
  while (!WiFi.smartConfigDone()) {
    delay(500);
    Serial.print(".");
  }

  // SmartConfig配置完成后
  smartConfigDoneHandle();
}