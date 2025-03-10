#include "cw2015.h"
#include <Wire.h>

uint8_t readRegister(uint8_t reg);
void writeRegister(uint8_t val, uint8_t reg);
uint16_t readAnalogVoltage(void);
float readBatVoltage(void);
int readBatQuantityLowPre(void);
float readBatQuantityHighPre(void);
void checkCW2015(void);
void CW2015setSleep(void);
void CW2015wakeUp(void);
void CW2015quickStart(void);
void CW2015powerReset(void);
void initCW2015(void);


// 读取寄存器，单字节
uint8_t readRegister(uint8_t reg) {
  uint8_t rdat;
  Wire.beginTransmission(CW_ADDR);
  Wire.write(reg);
  Wire.endTransmission();
  Wire.requestFrom(CW_ADDR, (uint8_t)1);
  rdat = Wire.read();
  return rdat;
}

// 写寄存器，单字节
void writeRegister(uint8_t val, uint8_t reg) {
  Wire.beginTransmission(CW_ADDR);
  Wire.write(reg);
  Wire.write(val);
  Wire.endTransmission();
}
extern void cw_update_config_info(void);
// 初始化IIC
void initCW2015(void) {
  Wire.begin(8, 7);
  cw_update_config_info();
}

// 读取adc量化数据14Bit
uint16_t readAnalogVoltage(void) {
  uint16_t AnalogVoltage = 0x0000;
  Wire.beginTransmission(CW_ADDR);
  Wire.write(CW_VCELL);
  Wire.endTransmission();
  Wire.requestFrom(CW_ADDR, (uint8_t)2);
  AnalogVoltage = Wire.read();
  AnalogVoltage <<= 8;
  AnalogVoltage += Wire.read();
  return (AnalogVoltage & 0x3fff);
}

// 电压
float readBatVoltage(void) {
  float Voltage = 0.0;
  uint16_t AnalogVoltage;
  AnalogVoltage = readAnalogVoltage();
  Voltage = AnalogVoltage * 0.000305;
  return Voltage;
}

// 读取电量，低精度1%
int readBatQuantityLowPre(void) {
  return readRegister(CW_SOC);
}

// 读取电量，高精度1/256%
float readBatQuantityHighPre(void) {
  float BatQuantity = 0.0;
  uint8_t BatQuantityH = readRegister(CW_SOC);
  uint8_t BatQuantityL = readRegister(CW_SOC + 1);
  BatQuantity = BatQuantityH + BatQuantityL / 256.0;
  return BatQuantity;
}

// 读版本寄存器，对比版本号
void checkCW2015(void) {
  uint8_t check;
  check = readRegister(CW_VERSION);
  if (check != 0x70) {
    Serial.println("cw2015 error!");  // 版本可能会有所不同
  } else {
    Serial.println("cw2015 ok!");
  }
}

// 进入睡眠模式
void CW2015setSleep(void) {
  writeRegister(0xc0, CW_MODE);
}

// 从睡眠模式中唤醒
void CW2015wakeUp(void) {
  writeRegister(0x00, CW_MODE);
}

// 快速启动
void CW2015quickStart(void) {
  writeRegister(0x30, CW_MODE);
}

// 电源复位
void CW2015powerReset(void) {
  writeRegister(0x0f, CW_MODE);
}
#define LVUSED 1
#include <string>
using std::string;
const char* getbat() {
  //CW2015wakeUp();
  //vTaskDelay(20);
  int BatQuantity = readBatQuantityLowPre();
  string bat = std::__cxx11::to_string(BatQuantity);
//CW2015setSleep();
//Serial.println(bat.c_str());
#ifdef LVUSED
  lv_label_set_text(ui_batvalue, bat.c_str());
#endif
  return bat.c_str();
}

// 更新电池建模信息
void cw_update_config_info(void) {
  uint8_t reg_buffer[4] = { MODE_NORMAL, CONFIG_UPDATE_FLG | ATHD_DEFAULT, MODE_RESTART, MODE_NORMAL | MODE_QUICK_START };
  static const unsigned char cw_bat_config_info[] = {
    0X15, 0X7E, 0X7C, 0X5C, 0X64, 0X6A, 0X65, 0X5C, 0X55, 0X53, 0X56, 0X61, 0X6F, 0X66, 0X50, 0X48,
    0X43, 0X42, 0X40, 0X43, 0X4B, 0X5F, 0X75, 0X7D, 0X52, 0X44, 0X07, 0XAE, 0X11, 0X22, 0X40, 0X56,
    0X6C, 0X7C, 0X85, 0X86, 0X3D, 0X19, 0X8D, 0X1B, 0X06, 0X34, 0X46, 0X79, 0X8D, 0X90, 0X90, 0X46,
    0X67, 0X80, 0X97, 0XAF, 0X80, 0X9F, 0XAE, 0XCB, 0X2F, 0X00, 0X64, 0XA5, 0XB5, 0X11, 0XD0, 0X11
  };

  // Make sure no in sleep mode
  writeRegister(reg_buffer[0], CW_MODE);

  // Update new battery info
  for (size_t i = 0; i < sizeof(cw_bat_config_info); i++) {
    writeRegister(cw_bat_config_info[i], REG_BATINFO + i);
  }

  // Set cw2015 to use new battery info
  writeRegister(reg_buffer[1], CW_CONFIG);

  // Restart
  writeRegister(reg_buffer[2], CW_MODE);

  // Work
  writeRegister(reg_buffer[3], CW_MODE);
}