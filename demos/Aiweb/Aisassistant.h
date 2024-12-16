#ifndef _AI_H
#define _AI_H
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <driver/i2s.h>
#include <UrlEncode.h>

#include <stdint.h>
#include <Arduino.h>
#include <stdint.h>



#ifdef __cplusplus 
extern "C" {
#endif  //__cplusplus 
const char * STT_GET(const char * access_token,uint8_t* audioData, int audioDataSize);
void TTS_GET(const char * access_token, const char * text);
void microphoneSetup();
void SoundSetup();
void CHATsetup();
#ifdef __cplusplus 
}
#endif  //__cplusplus

#endif