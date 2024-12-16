#include "ui.h"

#ifndef _WIFITASK_H
#define _WIFITASK_H






#ifdef __cplusplus
extern "C" {
#endif  //__cplusplus
int Wificonnect(const char* ssid, const char* password);
int Wificheck();
void Wificlose();
#ifdef __cplusplus
}
#endif  //__cplusplus

#endif