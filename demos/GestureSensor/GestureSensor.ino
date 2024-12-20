/*
  APDS-9960 - Gesture Sensor

  This example reads gesture data from the on-board APDS-9960 sensor of the
  Nano 33 BLE Sense and prints any detected gestures to the Serial Monitor.

  Gesture directions are as follows:
  - UP:    from USB connector towards antenna
  - DOWN:  from antenna towards USB connector
  - LEFT:  from analog pins side towards digital pins side
  - RIGHT: from digital pins side towards analog pins side

  The circuit:
  - Arduino Nano 33 BLE Sense

  This example code is in the public domain.
*/
#define tap0   35
#include <Arduino_APDS9960.h>
//#include "lv_port_indev.h"
void setup() {
  Serial.begin(115200);
  while (!Serial);
pinMode(tap0,INPUT);
  if (!APDS.begin()) {
    Serial.println("Error initializing APDS-9960 sensor!");
  }

  // for setGestureSensitivity(..) a value between 1 and 100 is required.
  // Higher values make the gesture recognition more sensitive but less accurate
  // (a wrong gesture may be detected). Lower values makes the gesture recognition
  // more accurate but less sensitive (some gestures may be missed).
  // Default is 80
 APDS.setGestureSensitivity(80);

  Serial.println("Detecting gestures ...");
}
void loop() {
  while(1){
if(digitalRead(tap0)==LOW){
  Serial.println("tap");
  delay(200);
  continue;
}
    
if (APDS.gestureAvailable()) {
    // a gesture was detected, read and print to Serial Monitor
    int gesture = APDS.readGesture();

    switch (gesture) {
      case GESTURE_UP:
        Serial.println("UP");
        break;

      case GESTURE_DOWN:
        Serial.println("DOWN");
        break;

      case GESTURE_LEFT:
        Serial.println("LEFT");
        break;

      case GESTURE_RIGHT:
        Serial.println("RIGHT");
        break;

      default:
        // ignore
        break;
    }
    delay(50);
    continue;
  }

    if (APDS.proximityAvailable()) {
    if(APDS.readProximity()==0){
      Serial.println("CLICK");
      delay(100);}

  }
  }
  
}
