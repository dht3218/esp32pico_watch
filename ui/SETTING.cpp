//设置相关的源码

#include "SETTING.h"
#include <EEPROM.h>
#include <WiFi.h>
#include "Wifitask.h"
#include <DNSServer.h>
#include <WebServer.h>
#include <ESPmDNS.h>                  //用于设备域名 MDNS.begin("esp32")
#include <esp_wifi.h>                 //用于esp_wifi_restore() 删除保存的wifi信息
#include <Update.h>                   // 引用相关库
const char* APset_SSID = "ESP32PICO";  //设置AP热点名称
String City = "";               //暂时存储心知天气城市


const int baudRate = 115200;  //设置波特率
const byte DNS_PORT = 53;     //设置DNS端口号
const int webPort = 80;       //设置Web端口号
const int resetPin = 0;       //设置重置按键引脚,用于删除WiFi信息

const char* AP_SSID = "ESP32PICO";      //设置AP热点名称
const char* AP_PASS = "12345678";  //设置AP热点密码
const char* HOST_NAME = "MY_ESP";   //设置设备名
String scanNetworksID = "";         //用于储存扫描到的WiFi ID
int connectTimeOut_s = 5;           //WiFi连接超时时间，单位秒
IPAddress apIP(192, 168, 4, 1);     //设置AP的IP地址
String wifi_ssid = "";              //暂时存储wifi账号密码
String wifi_pass = "";              //暂时存储wifi账号密码
//定义根目录首页网页HTML源代码
#define ROOT_HTML "<!DOCTYPE html><html><head><title>WIFI Config by dht</title><meta name=\"viewport\" http-equiv=\"Content-Type\" content=\"width=device-width, initial-scale=1,test/html;charset=utf-8\"></head><style type=\"text/css\">.input{display: block; margin-top: 10px;}.input span{width: 100px; float: left; float: left; height: 36px; line-height: 36px;}.input input{height: 30px;width: 200px;}.btn{width: 120px; height: 35px; background-color: #000000; border:0px; color:#ffffff; margin-top:15px; margin-left:100px;}</style><body><form method=\"POST\" action=\"configwifi\"><label class=\"input\"><span>WiFi名1</span><input type=\"text\" name=\"ssid\" value=\"\"></label><label class=\"input\"><span>WiFi密码1</span><input type=\"text\"  name=\"pass\"></label><label class=\"input\"><span>WiFi名2</span><input type=\"text\" name=\"ssid2\" value=\"\"></label><label class=\"input\"><span>WiFi密码2</span><input type=\"text\"  name=\"pass2\"></label><input class=\"btn\" type=\"submit\" name=\"submit\" value=\"上传\"> <p><span> 附近的 wifi: </P></form>"
//定义成功页面HTML源代码
#define SUCCESS_HTML "<html><body><font size=\"10\">successd,wifi connecting...<br />Please close this page manually.</font></body></html>"

DNSServer dnsServer;        //创建dnsServer实例
WebServer server(webPort);  //开启web服务, 创建TCP SERVER,参数: 端口号,最大连接数

bool shouldreboot = false;  // 重启标志，固件升级操作完成后设置该标志准备重启设备
//定义根目录首页网页HTML源代码
const char* ROOTset_HTML0 PROGMEM = R"=====(
<!DOCTYPE html>
<html>

<head>
  <meta charset='UTF-8'>
  <title>设备配置</title>
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <style type="text/css">
    body {
      display: flex;
      align-items: center;
      justify-content: center;
      flex-direction: column;
      background-color: #f5f5f5;
      margin: 0;
      padding: 0;
      height: 100vh;
      font-family: Arial, sans-serif;
    }

    .nav {
      display: flex;
      justify-content: center;
      position: fixed;
      bottom: 0;
      background-color: #f5f5f5;
      width: 100%;
      padding: 20px 0;
      box-shadow: 0px -2px 10px rgba(0, 0, 0, 0.1);
    }

    .nav-button {
      margin: 0 10px;
      padding: 8px 16px;
      background-color: #ebebeb;
      border: none;
      color: #333;
      font-size: 14px;
      cursor: pointer;
    }

    .nav-button.active {
      background-color: #ccc;
      font-weight: bold;
    }

    .page {
      display: none;
      padding: 20px;
      background-color: #fff;
      border-radius: 8px;
      margin-bottom: 70px;
    }

    .input {
      text-align: center;
      display: block;
      margin-top: 10px;
    }

    .input span {
      text-align: center;
      width: 150px;
      float: center;
      height: 36px;
      line-height: 36px;
      color: rgb(130, 175, 241);
    }

    .input input {
      text-align: center;
      height: 30px;
      width: 150px;
    }

    .btn {
      width: 120px;
      height: 35px;
      background-color: rgb(130, 175, 241);
      border: 0px;
      color: white;
      margin-top: 15px;
      margin-left: auto;
      margin-right: auto;
      display: block;
      border-radius: 8px;
      cursor: pointer;
    }
  </style>
  <script>
    function switchPage(pageId) {
      var buttons = document.getElementsByClassName("nav-button");
      for (var i = 0; i < buttons.length; i++) {
        buttons[i].classList.remove("active");
      }

      var pages = document.getElementsByClassName("page");
      for (var i = 0; i < pages.length; i++) {
        pages[i].style.display = "none";
      }

      var selectedButton = document.getElementById(pageId + "-button");
      selectedButton.classList.add("active");

      var selectedPage = document.getElementById(pageId);
      selectedPage.style.display = "block";
    }
  </script>
</head>

<body>
  <div id="wifi-page" class="page">
    <h1>WiFi配置</h1>
    <form method="POST" action="configwifi">
      <label class="input">
        <span>WiFi名称</span>
        <input type="text" name="ssid" value="">
      </label>
      <label class="input">
        <span>WiFi密码</span>
        <input type="text" name="pass">
      </label>
      <input class="btn" type="submit" name="submit" value="上传">
    </form>
  </div>

  <div id="settings-page" class="page">
    <h1>设置</h1>
    <form method="POST" action="configset">
    <label class="input">
      <span>音量</span>
      <input type="range" name="volume" min="0" max="3" value="50">
    </label>
    <label class="input">
      <span>城市</span>
      <input type="text" name="city" value="">
    </label>
    <input class="btn" type="submit" name="submit" value="保存设置">
    </form>
  </div>

  <div id="firmware-page" class="page">
    <h1>固件上传</h1>
    <form method='POST' action='/update' enctype='multipart/form-data'>
      <input style="display:block;margin-left:auto;margin-right:auto;margin-top:15px" type='file' name='firmware'>
      <input style="display:block;margin-left:auto;margin-right:auto;margin-top:15px" type='submit' style="color:blue" value="上传固件">
    </form>
    <p><span>下载固件：</span><a href="http://bin.bemfa.com/b/3BcN2ViMWFjNTk5NDA1NDc0ODlkN2E3NzllMjExMWExNTE=ota.bin">点击这里</a></p>
  </div>

  <div class="nav">
    <button id="wifi-page-button" class="nav-button active" onclick="switchPage('wifi-page')">WiFi配置</button>
    <button id="settings-page-button" class="nav-button" onclick="switchPage('settings-page')">设置</button>
    <button id="firmware-page-button" class="nav-button" onclick="switchPage('firmware-page')">固件上传</button>
  </div>

  <script>
    // 默认显示WiFi配置页面
    switchPage("wifi-page");
  </script>
</body>

</html>
)=====";


//定义成功页面HTML源代码
#define SUCCESSset_HTML "<html><body><font size=\"10\">successd<br />Please close this page manually.</font></body></html>"
String _updaterError = "";

//初始化AP模式
void initSoftAPset() {
  WiFi.mode(WIFI_AP);                                          //配置为AP模式
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));  //设置AP热点IP和子网掩码
  if (WiFi.softAP(APset_SSID)) {                               //开启AP热点,如需要密码则添加第二个参数
    //打印相关信息
    Serial.println("ESP-32 SoftAP is right.");
    Serial.print("Soft-AP IP address = ");
    Serial.println(WiFi.softAPIP());
    Serial.println(String("MAC address = ") + WiFi.softAPmacAddress().c_str());
  } else {  //开启热点失败
    Serial.println("WiFiAP Failed");
    delay(1000);
    Serial.println("restart now...");
    ESP.restart();  //重启复位esp32
  }
}

//初始化DNS服务器
void initDNSset() {
  //判断将所有地址映射到esp32的ip上是否成功
  if (dnsServer.start(DNS_PORT, "*", apIP)) {
    Serial.println("start dnsserver success.");
  } else {
    Serial.println("start dnsserver failed.");
  }
}
void handleResponse()  //回调函数
{
  server.sendHeader("Connection", "close");
  //if (Update.hasError()) {
  //  server.send(200, F("text/html"), String(F("Update error:")) + _updaterError);
  //}
  server.send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
}

void handleFileupload()  //回调函数
{
  HTTPUpload& upload = server.upload();    // 文件上传对象
  if (upload.status == UPLOAD_FILE_START)  // 文件上传开始
  {
    Serial.printf("开始上传文件: %s\n", upload.filename.c_str());
    if (!Update.begin())  // 开始固件升级，检查空可用间大小，如果正在升级或空间不够则返回false
    {
      Update.printError(Serial);
    }
  } else if (upload.status == UPLOAD_FILE_WRITE)  // 文件读写中
  {
    if (Update.write(upload.buf, upload.currentSize) != upload.currentSize)  // 将文件数据写入到OTA区域
    {
      Update.printError(Serial);
    }
  } else if (upload.status == UPLOAD_FILE_END)  // 文件上传完成
  {
    Serial.println("写入" + String(upload.totalSize) + "字节到OTA区域");
    if (!Update.end(true))  // 完成数据写入，设置在系统重启后自动将OTA区域固件移动到Sketch区域 // Update.begin不指定大小时这里设置true
    {
      Update.printError(Serial);
    }
    Serial.println("升级操作完成，模块将在1秒后重启以完成固件升级");
    shouldreboot = true;
  } else {
    Serial.printf("固件上传失败: status=%d\n", upload.status);
  }
}
void handleConfigWifi() {
  //返回http状态
  //server.send(200, "text/html", SUCCESS_HTML);
  if (server.hasArg("ssid")) {  //判断是否有账号参数
    Serial.print("got ssid:");
    wifi_ssid = server.arg("ssid");    //获取html表单输入框name名为"ssid"的内容
    EEPROM.writeString(1000, wifi_ssid);
    // strcpy(sta_ssid, server.arg("ssid").c_str());//将账号参数拷贝到sta_ssid中
    Serial.println(wifi_ssid);
  } else {  //没有参数
    Serial.println("error, not found ssid");
    server.send(200, "text/html", "<meta charset='UTF-8'>error, not found ssid");  //返回错误页面
    return;
  }
  //密码与账号同理
  if (server.hasArg("pass")) {
    Serial.print("got password:");
    wifi_pass = server.arg("pass");    //获取html表单输入框name名为"pwd"的内容
    EEPROM.writeString(1050, wifi_pass);
      //strcpy(sta_pass, server.arg("pass").c_str());
    Serial.println(wifi_pass);
  } else {
    Serial.println("error, not found password");
    server.send(200, "text/html", "<meta charset='UTF-8'>error, not found password");
    return;
  }
  EEPROM.commit();
  server.send(200, "text/html", "<meta charset='UTF-8'>SSID：" + wifi_ssid + "<br />password:" + wifi_pass + "<br />已取得WiFi信息,正在尝试连接,请手动关闭此页面。");  //返回保存成功页面
//   delay(1000);
//   WiFi.softAPdisconnect(true);  //参数设置为true，设备将直接关闭接入点模式，即关闭设备所建立的WiFi网络。
//   server.close();               //关闭web服务
//   WiFi.softAPdisconnect();      //在不输入参数的情况下调用该函数,将关闭接入点模式,并将当前配置的AP热点网络名和密码设置为空值.
  Serial.println("WiFi Connect SSID:" + wifi_ssid + "  PASS:" + wifi_pass);
}




//删除保存的wifi信息,并使LED闪烁5次
void restoreWiFi() {
  esp_wifi_restore();  //删除保存的wifi信息
  Serial.println("连接信息已清空,准备重启设备..");
}


//处理网站根目录“/”(首页)的访问请求,将显示配置wifi的HTML页面



void handleRootset() {
  // if (server.hasArg("selectSSID")) {
  //   server.send(200, "text/html", ROOT_HTML + scanNetworksID + "</body></html>");
  // } else {
  //   server.send(200, "text/html", ROOT_HTML + scanNetworksID + "</body></html>");
  // }
  if (server.hasArg("selectSSID")) {
    server.send(200, "text/html", ROOTset_HTML0 );
  } else {
    server.send(200, "text/html", ROOTset_HTML0);
  }
}
//提交数据后，返回给客户端信息函数
void handleSetting() {
  bool commit = false;
  bool hiku = false;
  bool history = false;
int volume=1;
String city="";
  if (server.hasArg("volume") && server.arg("volume").length() >= 0) {  //判断是否有参数
    volume = atoi((server.arg("volume")).c_str());    EEPROM.write(100, volume);
    Serial.println(volume);
    commit = true;
    
  }
  if (server.hasArg("city") && server.arg("volume").length() >= 0) {  //判断是否有参数
    city = server.arg("city");EEPROM.writeString(200, city);
    Serial.println(city);
    commit = true;
  }


  if (commit == true) {
    EEPROM.commit();
    server.send(200, "text/html", "<meta charset='UTF-8'>volume:" + String(volume) + "<br />city:" + city + "<br />已取得信息,请手动关闭此页面。");  //返回保存成功页面
    delay(200);
    WiFi.softAPdisconnect(true);  //参数设置为true，设备将直接关闭接入点模式，即关闭设备所建立的WiFi网络。
    server.close();               //关闭web服务
    WiFi.softAPdisconnect();      //在不输入参数的情况下调用该函数,将关闭接入点模式,并将当前配置的AP热点网络名和密码设置为空值.
    //PeiWangStart();
  }
}

// 设置处理404情况的函数'handleNotFoundset'
void handleNotFoundset() {  // 当浏览器请求的网络资源无法在服务器找到时通过此自定义函数处理
  handleRootset();          //访问不存在目录则返回配置页面
  //   server.send(404, "text/plain", "404: Not found");
}

//初始化WebServer
void initWebServerset() {
  //给设备设定域名esp32,完整的域名是esp32.local
  if (MDNS.begin("esp32")) {
    Serial.println("MDNS responder started");
  }
  //必须添加第二个参数HTTP_GET，以下面这种格式去写，否则无法强制门户
  server.on("/", HTTP_GET, handleRootset);            //  当浏览器请求服务器根目录(网站首页)时调用自定义函数handleRootset处理，设置主页回调函数，必须添加第二个参数HTTP_GET，否则无法强制门户
  server.on("/configset", HTTP_POST, handleSetting);  //  当浏览器请求服务器/configset(表单字段)目录时调用自定义函数handleSetting处理
  server.on("/update", HTTP_POST, handleResponse, handleFileupload);
  server.on("/configwifi", HTTP_POST, handleConfigWifi);

  server.onNotFound(handleNotFoundset);  //当浏览器请求的网络资源无法在服务器找到时调用自定义函数handleNotFound处理
  //Tells the server to begin listening for incoming connections.Returns None
  server.begin();  //启动TCP SERVER
                   //server.setNoDelay(true);                                  //关闭延时发送
  Serial.println("WebServer started!");
}
void setConfig() {
  initSoftAPset();
  initDNSset();
  initWebServerset();

}
int stopflag=0;

void startSetting() {stopflag=0;
  Serial.begin(baudRate);
  WiFi.hostname(HOST_NAME);  //设置设备名
  setConfig();
  do {
    dnsServer.processNextRequest();  //检查客户端DNS请求
    server.handleClient();           //检查客户端(浏览器)http请求
    if (shouldreboot) {
      delay(1000);
      ESP.restart();  // 重启设备
    }
    if (stopflag==1) {
      WiFi.softAPdisconnect(true);  //参数设置为true，设备将直接关闭接入点模式，即关闭设备所建立的WiFi网络。
      server.close();               //关闭web服务
      WiFi.softAPdisconnect();
      break;
    }
  } while (1);
}

int Wificonnection() {
  wifi_ssid=EEPROM.readString(1000);
  wifi_pass=EEPROM.readString(1050);
return Wificonnect(wifi_ssid.c_str(),wifi_pass.c_str());
}