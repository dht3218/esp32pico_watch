//#include <wakeup_detect_houguoxiong_inferencing.h>

#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <driver/i2s.h>
#include <UrlEncode.h>
#include <base64.hpp>

// I2S config for MAX98357A
#define I2S_OUT_PORT I2S_NUM_1
#define I2S_OUT_BCLK 14
#define I2S_OUT_LRC 2
#define I2S_OUT_DOUT 27

// INMP441 config
#define I2S_IN_PORT I2S_NUM_0
#define I2S_IN_BCLK 14
#define I2S_IN_LRC 2
#define I2S_IN_DIN 27

// WiFi credentials
const char* ssid = "dht";
const char* password = "12345678";

// Baidu API credentials
const char* baidu_api_key =  "*";
const char* baidu_secret_key = "*";

// Baidu 千帆大模型
char* qianfan_api_key =  "*";
char* qianfan_secret_key =  "*";




// Audio recording settings
#define SAMPLE_RATE 16000
#define RECORD_TIME_SECONDS 10
#define BUFFER_SIZE (SAMPLE_RATE * RECORD_TIME_SECONDS)

// // 唤醒词阈值，阈值越大，要求识别的唤醒词更精准
// #define PRED_VALUE_THRESHOLD 0.8

// /** Audio buffers, pointers and selectors */
// typedef struct {
//   int16_t* buffer;
//   uint8_t buf_ready;
//   uint32_t buf_count;
//   uint32_t n_samples;
// } inference_t;

// static inference_t inference;
// static const uint32_t sample_buffer_size = 2048;
// static signed short sampleBuffer[sample_buffer_size];
// static bool debug_nn = false;  // Set this to true to see e.g. features generated from the raw signal
// static bool record_status = false;
void microphoneSetup() {
  i2s_driver_uninstall(I2S_OUT_PORT);
  Serial.println("microphoneSetup");
  pinMode(20, OUTPUT);
  digitalWrite(20, HIGH);
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  // Initialize I2S for audio input
  i2s_config_t i2s_config_in = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX),
    .sample_rate = SAMPLE_RATE,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,  // 注意：INMP441 输出 32 位数据
    .channel_format = I2S_CHANNEL_FMT_ONLY_RIGHT,
    .communication_format = i2s_comm_format_t(I2S_COMM_FORMAT_STAND_I2S),
    .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
    .dma_buf_count = 8,
    .dma_buf_len = 1024,
  };
  i2s_pin_config_t pin_config_in = {
    .bck_io_num = I2S_IN_BCLK,
    .ws_io_num = I2S_IN_LRC,
    .data_out_num = -1,
    .data_in_num = I2S_IN_DIN
  };
  i2s_driver_install(I2S_IN_PORT, &i2s_config_in, 0, NULL);
  i2s_set_pin(I2S_IN_PORT, &pin_config_in);
}

void SoundSetup() {
  i2s_driver_uninstall(I2S_IN_PORT);
  Serial.println("SoundSetup");
  pinMode(20, OUTPUT);
  digitalWrite(20, LOW);
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  // Initialize I2S for audio output
  i2s_config_t i2s_config_out = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX),
    .sample_rate = SAMPLE_RATE,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
    .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
    .communication_format = (i2s_comm_format_t)(I2S_COMM_FORMAT_STAND_I2S),
    .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
    .dma_buf_count = 8,
    .dma_buf_len = 512,
  };
  i2s_pin_config_t pin_config = {
    .bck_io_num = I2S_OUT_BCLK,
    .ws_io_num = I2S_OUT_LRC,
    .data_out_num = I2S_OUT_DOUT,
    .data_in_num = -1
  };
  i2s_driver_install(I2S_OUT_PORT, &i2s_config_out, 0, NULL);
  i2s_set_pin(I2S_OUT_PORT, &pin_config);
}

extern void mainChat(void* arg);
void setup() {
  // 设置串口波特率
  Serial.begin(115200);

  // 设置LED输出模式，并初始化设置为低
  // pinMode(LED_BUILTIN, OUTPUT);
  // digitalWrite(LED_BUILTIN, LOW);  //Turn off

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  microphoneSetup();


  // // 开启对话主流程
  xTaskCreate(mainChat, "mainChat", 1024 * 32, NULL, 10, NULL);

  // summary of inferencing settings (from model_metadata.h)
  // ei_printf("Inferencing settings:\n");
  // ei_printf("\tInterval: ");
  // ei_printf_float((float)EI_CLASSIFIER_INTERVAL_MS);
  // ei_printf(" ms.\n");
  // ei_printf("\tFrame size: %d\n", EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE);
  // ei_printf("\tSample length: %d ms.\n", EI_CLASSIFIER_RAW_SAMPLE_COUNT / 16);
  // ei_printf("\tNo. of classes: %d\n", sizeof(ei_classifier_inferencing_categories) / sizeof(ei_classifier_inferencing_categories[0]));

  // ei_printf("\nStarting continious inference in 2 seconds...\n");
  // ei_sleep(2000);

  // if (microphone_inference_start(EI_CLASSIFIER_RAW_SAMPLE_COUNT) == false) {
  //   ei_printf("ERR: Could not allocate audio buffer (size %d), this could be due to the window length of your model\r\n", EI_CLASSIFIER_RAW_SAMPLE_COUNT);
  //   return;
  // }

  // ei_printf("Recording...\n");
}

/**
 * @brief      Arduino main function. Runs the inferencing loop.
 */
void loop() {
  // bool m = microphone_inference_record();
  // if (!m) {
  //   Serial.println("ERR: Failed to record audio...");
  //   //ei_printf("ERR: Failed to record audio...\n");
  //   return;
  // }

  // signal_t signal;
  // signal.total_length = EI_CLASSIFIER_RAW_SAMPLE_COUNT;
  // signal.get_data = &microphone_audio_signal_get_data;
  // ei_impulse_result_t result = { 0 };

  // EI_IMPULSE_ERROR r = run_classifier(&signal, &result, debug_nn);
  // if (r != EI_IMPULSE_OK) {
  //   ei_printf("ERR: Failed to run classifier (%d)\n", r);
  //   return;
  // }

  // int pred_index = -1;                      // Initialize pred_index
  // float pred_value = PRED_VALUE_THRESHOLD;  // Initialize pred_value

  // // print the predictions
  // ei_printf("Predictions ");
  // ei_printf("(DSP: %d ms., Classification: %d ms., Anomaly: %d ms.)",
  //           result.timing.dsp, result.timing.classification, result.timing.anomaly);
  // ei_printf(": \n");
  // for (size_t ix = 0; ix < EI_CLASSIFIER_LABEL_COUNT; ix++) {
  //   ei_printf("    %s: ", result.classification[ix].label);
  //   ei_printf_float(result.classification[ix].value);
  //   ei_printf("\n");

  //   // 唤醒词在第一位，此时判断classification[0]位置大于阈值表示唤醒，如果你的唤醒词在第2位，则需要判断classification[1]，第3位就是classification[2]
  //   if (result.classification[0].value > pred_value) {
  //     pred_index = 0;
  //   }
  // }
  // // Display inference result
  // if (pred_index == 0) {
  //   digitalWrite(LED_BUILTIN, HIGH);  //Turn on

  //   Serial.println("playAudio_Zai");

  //   playAudio_Zai();

  //   record_status = false;
  // }

  // #if EI_CLASSIFIER_HAS_ANOMALY == 1
  //   ei_printf("    anomaly score: ");
  //   ei_printf_float(result.anomaly);
  //   ei_printf("\n");
  // #endif
}

// static void audio_inference_callback(uint32_t n_bytes) {
//   for (int i = 0; i < n_bytes >> 1; i++) {
//     inference.buffer[inference.buf_count++] = sampleBuffer[i];

//     if (inference.buf_count >= inference.n_samples) {
//       inference.buf_count = 0;
//       inference.buf_ready = 1;
//     }
//   }
// }

// static void capture_samples(void* arg) {

//   const int32_t i2s_bytes_to_read = (uint32_t)arg;
//   size_t bytes_read = i2s_bytes_to_read;

//   while (1) {

//     if (record_status) {
//       /* read data at once from i2s - Modified for XIAO ESP2S3 Sense and I2S.h library */
//       i2s_read(I2S_IN_PORT, (void*)sampleBuffer, i2s_bytes_to_read, &bytes_read, 100);
//       // esp_i2s::i2s_read(esp_i2s::I2S_NUM_0, (void *)sampleBuffer, i2s_bytes_to_read, &bytes_read, 100);

//       if (bytes_read <= 0) {
//         ei_printf("Error in I2S read : %d", bytes_read);
//       } else {
//         if (bytes_read < i2s_bytes_to_read) {
//           ei_printf("Partial I2S read");
//         }

//         // scale the data (otherwise the sound is too quiet)
//         for (int x = 0; x < i2s_bytes_to_read / 2; x++) {
//           sampleBuffer[x] = (int16_t)(sampleBuffer[x]) * 8;
//         }

//         audio_inference_callback(i2s_bytes_to_read);
//       }
//     }
//     delay(1);
//   }
//   vTaskDelete(NULL);
// }

/**
 * @brief      Init inferencing struct and setup/start PDM
 *
 * @param[in]  n_samples  The n samples
 *
 * @return     { description_of_the_return_value }
 */
// static bool microphone_inference_start(uint32_t n_samples) {
//   inference.buffer = (int16_t*)malloc(n_samples * sizeof(int16_t));

//   if (inference.buffer == NULL) {
//     return false;
//   }

//   inference.buf_count = 0;
//   inference.n_samples = n_samples;
//   inference.buf_ready = 0;

//   ei_sleep(100);

//   record_status = true;

//   xTaskCreate(capture_samples, "CaptureSamples", 1024 * 32, (void*)sample_buffer_size, 10, NULL);

//   return true;
// }

/**
 * @brief      Wait on new data
 *
 * @return     True when finished
 */
// static bool microphone_inference_record(void) {
//   bool ret = true;

//   while (inference.buf_ready == 0) {
//     delay(10);
//   }

//   inference.buf_ready = 0;
//   return ret;
// }

/**
 * Get raw audio signal data
 */
// static int microphone_audio_signal_get_data(size_t offset, size_t length, float* out_ptr) {
//   numpy::int16_to_float(&inference.buffer[offset], out_ptr, length);

//   return 0;
// }

// /**
//  * @brief      Stop PDM and release buffers
//  */
// static void microphone_inference_end(void) {
//   free(sampleBuffer);
//   ei_free(inference.buffer);
// }

// #if !defined(EI_CLASSIFIER_SENSOR) || EI_CLASSIFIER_SENSOR != EI_CLASSIFIER_SENSOR_MICROPHONE
// #error "Invalid model for current sensor."
// #endif

void mainChat(void* arg) {
  //获取access token
  String baidu_access_token = "";
  String qianfan_access_token = "";

  baidu_access_token = getAccessToken(baidu_api_key, baidu_secret_key);
  qianfan_access_token = getAccessToken(qianfan_api_key, qianfan_secret_key);

  while (1) {
    if (1) {
      // Record audio from INMP441
      // 分配内存
      uint8_t* pcm_data = (uint8_t*)ps_malloc(BUFFER_SIZE);
      if (!pcm_data) {
        Serial.println("Failed to allocate memory for pcm_data");
        return;
      }

      Serial.println("i2s_read");
      // 开始循环录音，将录制结果保存在pcm_data中
      size_t bytes_read = 0, recordingSize = 0, ttsSize = 0;
      int16_t data[512];
      size_t noVoicePre = 0, noVoiceCur = 0, noVoiceTotal = 0, VoiceCnt = 0;
      bool recording = true;

      while (1) {
        // 记录刚开始的时间
        noVoicePre = millis();

        // i2s录音
        esp_err_t result = i2s_read(I2S_IN_PORT, data, sizeof(data), &bytes_read, portMAX_DELAY);
        memcpy(pcm_data + recordingSize, data, bytes_read);
        recordingSize += bytes_read;
        Serial.printf("%x recordingSize: %d bytes_read :%d\n", pcm_data + recordingSize, recordingSize, bytes_read);

        // 计算平均值
        uint32_t sum_data = 0;
        for (int i = 0; i < bytes_read / 2; i++) {
          sum_data += abs(data[i]);
        }
        sum_data = sum_data / bytes_read;
        Serial.printf("sum_data :%d\n", sum_data);

        // 判断当没有说话时间超过一定时间时就退出录音
        noVoiceCur = millis();
        if (sum_data < 15) {
          noVoiceTotal += noVoiceCur - noVoicePre;
        } else {
          noVoiceTotal = 0;
          VoiceCnt += 1;
        }
        Serial.printf("noVoiceCur :%d noVoicePre :%d noVoiceTotal :%d\n", noVoiceCur, noVoicePre, noVoiceTotal);

        if (noVoiceTotal > 1000) {
          recording = false;
        }

        if (!recording || (recordingSize >= BUFFER_SIZE - bytes_read)) {
          Serial.printf("record done: %d", recordingSize);

          break;
        }
      }

      // 设置唤醒录音状态为true，此后可以唤醒
      //record_status = true;

      // 此时一直没有说话，则退出被唤醒状态
      if (VoiceCnt == 0) {
        //digitalWrite(LED_BUILTIN, LOW);  //Turn off

        recordingSize = 0;

        // 释放内存
        free(pcm_data);

        continue;
      }
      playAudio_Zai();
      if (recordingSize > 0) {
        // 音频转文本（语音识别API访问）
        String recognizedText = baiduSTT_Send(baidu_access_token, pcm_data, recordingSize);
        Serial.println("Recognized text: " + recognizedText);

        // 访问千帆大模型（LLM大模型API访问）
        String ernieResponse = baiduErnieBot_Get(qianfan_access_token, recognizedText.c_str());
        //星火大模型
        // String ernieResponse  = getXunFeiAnswer(recognizedText);
        Serial.println("Ernie Bot response: " + ernieResponse);
        //SoundSetup();
        // 文本转音频tts并通过MAX98357A输出（语音合成API访问）
        baiduTTS_Send(baidu_access_token, ernieResponse);
        // Serial.println("ttsSize: ");
        // Serial.println(ttsSize);
        //delay(100);
        microphoneSetup();
      }

      // 释放内存
      free(pcm_data);

      // 设置唤醒录音状态为false，此后继续录音对话
      //record_status = false;
    }
    delay(10);
  }
}

// Get Baidu API access token
String getAccessToken(const char* api_key, const char* secret_key) {
  String access_token = "";
  HTTPClient http;

  // 创建http请求
  http.begin("https://aip.baidubce.com/oauth/2.0/token?grant_type=client_credentials&client_id=" + String(api_key) + "&client_secret=" + String(secret_key));
  int httpCode = http.POST("");

  if (httpCode == HTTP_CODE_OK) {
    String response = http.getString();
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, response);
    access_token = doc["access_token"].as<String>();

    Serial.printf("[HTTP] GET access_token: %s\n", access_token);
  } else {
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }
  http.end();

  return access_token;
}

String baiduSTT_Send(String access_token, uint8_t* audioData, int audioDataSize) {
  String recognizedText = "";

  if (access_token == "") {
    Serial.println("access_token is null");
    return recognizedText;
  }

  // audio数据包进行Base64编码，数据量会增大1/3
  int audio_data_len = audioDataSize * sizeof(char) * 1.4;
  unsigned char* audioDataBase64 = (unsigned char*)ps_malloc(audio_data_len);
  if (!audioDataBase64) {
    Serial.println("Failed to allocate memory for audioDataBase64");
    return recognizedText;
  }

  // json包大小，由于需要将audioData数据进行Base64的编码，数据量会增大1/3
  int data_json_len = audioDataSize * sizeof(char) * 1.4;
  char* data_json = (char*)ps_malloc(data_json_len);
  if (!data_json) {
    Serial.println("Failed to allocate memory for data_json");
    return recognizedText;
  }

  // Base64 encode audio data
  encode_base64(audioData, audioDataSize, audioDataBase64);

  memset(data_json, '\0', data_json_len);
  strcat(data_json, "{");
  strcat(data_json, "\"format\":\"pcm\",");
  strcat(data_json, "\"rate\":16000,");
  strcat(data_json, "\"dev_pid\":1537,");
  strcat(data_json, "\"channel\":1,");
  strcat(data_json, "\"cuid\":\"57722200\",");
  strcat(data_json, "\"token\":\"");
  strcat(data_json, access_token.c_str());
  strcat(data_json, "\",");
  sprintf(data_json + strlen(data_json), "\"len\":%d,", audioDataSize);
  strcat(data_json, "\"speech\":\"");
  strcat(data_json, (const char*)audioDataBase64);
  strcat(data_json, "\"");
  strcat(data_json, "}");

  // 创建http请求
  HTTPClient http_client;

  http_client.begin("http://vop.baidu.com/server_api");
  http_client.addHeader("Content-Type", "application/json");
  int httpCode = http_client.POST(data_json);

  if (httpCode > 0) {
    if (httpCode == HTTP_CODE_OK) {
      // 获取返回结果
      String response = http_client.getString();
      Serial.println(response);

      // 从json中解析对应的result
      DynamicJsonDocument responseDoc(2048);
      deserializeJson(responseDoc, response);
      recognizedText = responseDoc["result"].as<String>();
    }
  } else {
    Serial.printf("[HTTP] POST failed, error: %s\n", http_client.errorToString(httpCode).c_str());
  }

  // 释放内存
  if (audioDataBase64) {
    free(audioDataBase64);
  }

  if (data_json) {
    free(data_json);
  }

  http_client.end();

  return recognizedText;
}

// Get response from Baidu Ernie Bot
String baiduErnieBot_Get(String access_token, String prompt) {
  String ernieResponse = "";

  if (access_token == "") {
    Serial.println("access_token is null");
    ernieResponse = "获取access token失败";
    return ernieResponse;
  }

  if (prompt.length() == 0) {
    ernieResponse = "识别出错了";
    return ernieResponse;
  }

  // 角色设定
  prompt += "你是一个语音助手，类似朋友的角色进行回答下面的问题，并且要求最多20个字简短的回答。";

  // 创建http, 添加访问url和头信息
  HTTPClient http;

  // 千帆大模型API
  const char* ernie_api_url = "https://aip.baidubce.com/rpc/2.0/ai_custom/v1/wenxinworkshop/chat/completions_pro?access_token=";

  http.begin(ernie_api_url + String(access_token));
  http.addHeader("Content-Type", "application/json");

  // 创建一个 JSON 文档
  DynamicJsonDocument doc(2048);

  // 创建 messages 数组
  JsonArray messages = doc.createNestedArray("messages");

  // 创建 message 对象并添加到 messages 数组
  JsonObject message = messages.createNestedObject();
  message["role"] = "user";
  message["content"] = prompt;

  // 添加其他字段
  doc["disable_search"] = false;
  doc["enable_citation"] = false;

  // 将 JSON 数据序列化为字符串
  String requestBody;
  serializeJson(doc, requestBody);

  // 发送http访问请求
  int httpCode = http.POST(requestBody);

  // 访问结果的判断
  if (httpCode == HTTP_CODE_OK) {
    // 获取返回结果并解析
    String response = http.getString();
    Serial.println(response);

    DynamicJsonDocument responseDoc(2048);
    deserializeJson(responseDoc, response);

    ernieResponse = responseDoc["result"].as<String>();
  } else {
    Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }

  // 结束http访问
  http.end();

  // 返回响应数据
  return ernieResponse;
}

void baiduTTS_Send(String access_token, String text) {
  if (access_token == "") {
    Serial.println("access_token is null");
    return;
  }

  if (text.length() == 0) {
    Serial.println("text is null");
    return;
  }

  const int per = 1;
  const int spd = 5;
  const int pit = 5;
  const int vol = 10;
  const int aue = 6;

  // 进行 URL 编码
  String encodedText = urlEncode(urlEncode(text));

  // URL http请求数据封装
  String url = "https://tsn.baidu.com/text2audio";

  const char* header[] = { "Content-Type", "Content-Length" };

  url += "?tok=" + access_token;
  url += "&tex=" + encodedText;
  url += "&per=" + String(per);
  url += "&spd=" + String(spd);
  url += "&pit=" + String(pit);
  url += "&vol=" + String(vol);
  url += "&aue=" + String(aue);
  url += "&cuid=esp32";
  url += "&lan=zh";
  url += "&ctp=1";

  // http请求创建
  HTTPClient http;

  http.begin(url);
  http.collectHeaders(header, 2);

  // http请求
  int httpResponseCode = http.GET();
  if (httpResponseCode > 0) {
    if (httpResponseCode == HTTP_CODE_OK) {
      String contentType = http.header("Content-Type");
      Serial.println(contentType);
      if (contentType.startsWith("audio")) {
        Serial.println("合成成功");
        SoundSetup();
        int len = http.getSize();
        // 获取返回的音频数据流
        Stream* stream = http.getStreamPtr();
        uint8_t buffer[512];
        uint8_t bufferold[512] = { 0 };
        size_t bytesRead = 0;

        //Serial.println(stream);
        // 设置timeout为200ms 避免最后出现杂音
        stream->setTimeout(200);

        //Serial.println("播放回答");
        //size_t bytesRead = 0;
        int i = 0;
        size_t totalBytesRead = 0;                            // 用于记录总字节数
        while (http.connected() && (len > 0 || len == -1)) {  //http.connected() && (bytesRead = stream->readBytes(buffer, sizeof(buffer))
          // 音频输出
          size_t size = stream->available();
          if (size) {
            // read up to 512 byte
            bytesRead = stream->readBytes(buffer, ((size > sizeof(buffer)) ? sizeof(buffer) : size));
            // if (buffer[0] == bufferold[0] && buffer[2] == bufferold[2] && buffer[10] == bufferold[10] && buffer[40] == bufferold[40] && buffer[28] == bufferold[28]){
            //   Serial.println("重复");continue;
            // } 
            // vTaskDelay(1000);
            memcpy(bufferold, buffer, sizeof(buffer));
            //Serial.println(bytesRead);
            //for (int j=0; j < sizeof(buffer); j++) buffer[j] *= 8;
            if (bytesRead > 0) {
              size_t bytesWritten = 0;//i += 1;Serial.println(i);
              i2s_write(I2S_OUT_PORT, (int16_t*)buffer, bytesRead, &bytesWritten, portMAX_DELAY);
              memset(buffer, 0, sizeof(buffer));  
            }
            if (len > 0) {
              len -= bytesRead;
            }
            //
          }

          delay(1);
          totalBytesRead += bytesRead;
          //printf("Read %d bytes\n", bytesRead);
          // if (bytesRead > 0) {
          //   size_t bytesWritten = 0;
          //   i2s_write(I2S_OUT_PORT, (int16_t*)buffer, bytesRead, &bytesWritten, portMAX_DELAY);
          //   //printf("Written %d bytes to I2S\n", bytesWritten);
          //   //vTaskDelay(9);

          //   // if (bytesWritten < bytesRead) {
          //   //  // printf("Warning: Not all bytes were written to I2S\n");
          //   // }
          //   memset(buffer, 0, sizeof(buffer));
          // }
          // playAudio(buffer, bytesRead);
          // delay(10);
        }
        Serial.println("播放回答");
        Serial.println(totalBytesRead);
        // 清空I2S DMA缓冲区
        delay(200);
        clearAudio();
      } else if (contentType.equals("application/json")) {
        Serial.println("合成出现错误");
      } else {
        Serial.println("未知的Content-Type");
      }
    } else {
      Serial.println("Failed to receive audio file");
    }
  } else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  http.end();
}

// Play audio data using MAX98357A
void playAudio(uint8_t* audioData, size_t audioDataSize) {
  //Serial.println("playAudio");
  if (audioDataSize > 0) {
    // 发送
    //for(int j=0;j<audioDataSize;j++)Serial.println(audioData[j]);
    ///Serial.println(audioDataSize);
    size_t bytes_written = 0;
    i2s_write(I2S_OUT_PORT, (int16_t*)audioData, audioDataSize, &bytes_written, portMAX_DELAY);
    //Serial.println("b");
  }
}

void clearAudio(void) {
  // 清空I2S DMA缓冲区
  i2s_zero_dma_buffer(I2S_OUT_PORT);
  Serial.println("clearAudio");
}

// Play zai audio data using MAX98357A
void playAudio_Zai(void) {
  SoundSetup();
  const char* zai = "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AAAEAAoACAAKAAwAEgAYACQANAA6AEYAYgB8AIQAhgCUAJ4AmgCSAJQAkgCOAIoAgAB6AHYAcgBoAGQAaABkAF4AYACAAKwA3gAAAQoBCgEAAeoA2gDcAMoAugCmAJwAigBkADYAHAAiACgAHAACAP7/CgAYAC4APgBCAEYAOgAyACwAPgBGAD4AJgACAN7/wP+y/7j/xP/O/9D/vv+q/5T/jP+K/5b/sP/M/+D/5P/U/7r/ov+Y/6L/uv/Y/+z/7P/Y/7r/nv+U/57/sP/G/9D/1v/Q/8L/rv+g/57/pP+0/8r/3P/g/9r/zP/C/8L/0v/u/wIADAAOAAYA/v/2//z/CgAWABgAGgAaABgAEgAOABIAEgAWABgAHgAgABwAFAAOAAwADAAOABIAFAASAA4ACgAGAAIAAAD6//j/8v/y//b/+v/+/wAAAAAAAP7/AAAAAAgADAAQABQADgAMAAwACAACAAoACAAKAA4ACgAGAAAA/v8CABAAGAAYABwAHgASABYAGgAaABoAGAAUAAoAAAD+//b/7v/s/+r/6P/0//L/8v/0//j/AAAAAAQADgAWACAAHgAYABYAFAAQABQAGAAQAAYA/v/4//z//v8AAAIACAAOABIAFAAUABIAEgAWABgAHAAaABQACgAGAAYACAAMABAAFgASABAACAACAAIACAAMABAAEAAIAAIA/P/2//T/+v/8/wQACgAEAP7/8P/q/+b/8P/s/+7/8v/6//T/4v/o/+7/6P/q//L/9v/2//D/5P/m/+r/7v/0//7/AAAAAPj/8P/o/+z/9P/4/wQABAAAAPz/8v/4//r//v8EAAgACgAGAAYABAAAAAQADAAUABoAHAAWABAACgAEABAAFAAcABgAFAAKAAIAAgACAAwACgAQABAAEgAQABAAEgASABgAGAAeACAAHAAgAB4AHgAeABwAIAAeACAAHAAYABgAFAAQAA4ADgAMAAwADAAQABAAEgAUABYAGgAeACIAIgAmACAAIAAeABgAFgAWABIAEgAGAAQABgAEAAYABAAIABQAHAAiACIAIgAiACAAHgAiACgAHgAYABQAEAASAAoACAAEAP7//P/8//7//P/8//z//P/+/wAAAAAEAAgACAAIAAYABAAAAAAAAgAAAPz/+v/2//b/+v/6//b/+P/0//j/+v/4//r/9P/2//T/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AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA=";

  // 分配内存
  uint8_t* decode_data = (uint8_t*)ps_malloc(16000 * 3);
  if (!decode_data) {
    Serial.println("Failed to allocate memory for decode_data");
    return;
  }

  // base64 解析
  int decoded_length = decode_base64((unsigned char*)zai, (unsigned char*)decode_data);

  // 播放
  playAudio(decode_data, decoded_length);

  // delay 200ms
  delay(200);

  // 清空I2S DMA缓冲区
  clearAudio();

  // 释放内存
  free(decode_data);
  microphoneSetup();
}

