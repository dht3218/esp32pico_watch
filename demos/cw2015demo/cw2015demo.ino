
#include "cw2015.h"
/**
 * Hardware Connections:
 * -VCC = 3.3V
 * -GND = GND
 * -SDA = 18 (use inline 330 ohm resistor if your board is 5V)
 * -SCL = 23 (use inline 330 ohm resistor if your board is 5V)
 */
// TwoWire I2Cone = TwoWire(0);
// CW2015 cw2015(&I2Cone);

void setup() {
  Serial.begin(115200);
  //pinMode(22, INPUT);
  Wire.begin(8, 7);
  //I2Cone.begin(8,7, 400000UL);   //SDA0,SCL0
  //initCW2015();
  delay(100);
  Serial.println("Sensor init finish!");
  //cw_2015.powerReset();
  wakeUp();
  delay(100);
  cw_update_config_info();
  //cw2015.checkCW2015();
}

void loop() {
  wakeUp();
  delay(500);
  float val = readBatVoltage();

  float eleq = readBatQuantityHighPre();
  //setSleep();
  Serial.print("Time:");
  Serial.print(millis());  // Get the system time from Arduino
  Serial.print(" val:");
  Serial.print(val, 1);  // Only print one decimal place
  Serial.print("V");
  Serial.print(" eleq:");
  Serial.print(eleq);  // Only print one decimal place
  Serial.print("%");
  Serial.println();

  delay(1000);
}