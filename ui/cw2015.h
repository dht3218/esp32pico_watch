#ifndef __CW2015_H__
#define __CW2015_H__

#include <Arduino.h>
#include "ui.h"

#define CW_ADDR 0X62
#define CW_VERSION 0x00
#define CW_VCELL 0x02
#define CW_SOC 0x04
#define CW_RRT_ALET 0x06
#define CW_CONFIG 0x08
#define CW_MODE 0x0a

#define CW_ADDR 0X62
#define CW_VERSION 0x00
#define CW_VCELL 0x02
#define CW_SOC 0x04
#define CW_RRT_ALET 0x06
#define CW_CONFIG 0x08
#define CW_MODE 0x0a
#define CW_MODE 0x0a
#define CW_CONFIG 0x08
#define REG_BATINFO 0x10
#define MODE_NORMAL 0x00
#define MODE_RESTART 0x08
#define MODE_QUICK_START 0x30
#define CONFIG_UPDATE_FLG 0x01
#define ATHD_DEFAULT 0x02




#ifdef __cplusplus
extern "C" {
#endif
 void cw_update_config_info(void);
  const char* getbat();
  void CW2015wakeUp();
#ifdef __cplusplus
} /*extern "C"*/
#endif
#endif