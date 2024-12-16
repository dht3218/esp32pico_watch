#ifndef __CW2015_H__
#define __CW2015_H__
 
#include <Arduino.h>
#include <Wire.h> 
 
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

uint8_t readRegister(uint8_t reg);
void writeRegister(uint8_t val, uint8_t reg);
uint16_t readAnalogVoltage(void);
float readBatVoltage(void);
int readBatQuantityLowPre(void);
float readBatQuantityHighPre(void);
void checkCW2015(void);
void setSleep(void);
void wakeUp(void);
void quickStart(void);
void powerReset(void);
void initCW2015(void);
void cw_update_config_info(void);
// class CW2015
// {
// public:
 
//   CW2015(TwoWire *pWire=&Wire);
 
//   void initCW2015(void);
 
//   uint16_t readAnalogVoltage(void);
 
//   uint8_t readBatQuantityLowPre(void);//低精度%1
 
//   float readBatQuantityHighPre(void);//高精度1/256%
  
//   float readBatVoltage(void);//电压
 
//   void checkCW2015(void);
 
//   void setSleep(void);
 
//   void wakeUp(void);
 
//   void quickStart(void);
 
//   void powerReset(void);
 
// protected:
 
// byte readRegister(byte reg);
 
// void writeRegister(byte val,byte reg);
 
// private:
//   uint8_t _addr;   // I2C communication address of CW2015
//   TwoWire *_pWire;   // The pointer to I2C communication method
// };
 
#endif