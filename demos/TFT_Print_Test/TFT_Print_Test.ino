/*  
 Test the tft.print() viz embedded tft.write() function

 This sketch used font 2, 4, 7

 Make sure all the display driver and pin comnenctions are correct by
 editting the User_Setup.h file in the TFT_eSPI library folder.

 #########################################################################
 ###### DON'T FORGET TO UPDATE THE User_Setup.h FILE IN THE LIBRARY ######
 #########################################################################
 */


#include <TFT_eSPI.h> // Graphics and font library for ILI9341 driver chip
#include <SPI.h>
#include <Arduino_APDS9960.h>
#define TFT_GREY 0x5AEB // New colour

TFT_eSPI tft = TFT_eSPI();  // Invoke library


void setup(void) {

  Serial.begin(115200);
    pinMode(4,OUTPUT);
  digitalWrite(4,HIGH);
   pinMode(25,OUTPUT);
  digitalWrite(25,LOW); 
  tft.init();Serial.println("tftinit");
  tft.setRotation(2);

    tft.setCursor(100, 80, 10);
  // Set the font colour to be white with a black background, set text size multiplier to 1
  tft.setTextColor(TFT_WHITE,TFT_BLACK);  tft.setTextSize(1);
  tft.println("Hello World!");
      if (!APDS.begin()) {
    Serial.println("Error initializing APDS-9960 sensor!");
  }
  tft.fillScreen(TFT_GREY);
}

void loop() {
  
  // Fill screen with grey so we can see the effect of printing with and without 
  // a background colour defined
  
  
  // Set "cursor" at top left corner of display (0,0) and select font 2
  // (cursor will move to next line automatically during printing with 'tft.println'
  //  or stay on the line is there is room for the text with tft.print)
  tft.setCursor(100, 80, 2);
  // Set the font colour to be white with a black background, set text size multiplier to 1
  tft.setTextColor(TFT_WHITE,TFT_BLACK);  tft.setTextSize(10);
 // Serial.println("Detecting gestures ...");
  // We can now plot text on screen using the "print" class
  if (APDS.gestureAvailable()) {
    // a gesture was detected, read and print to Serial Monitor
    int gesture = APDS.readGesture();

    switch (gesture) {
      case GESTURE_UP:
        Serial.println("Detected UP gesture");
        tft.println("1");
        break;

      case GESTURE_DOWN:
        Serial.println("Detected DOWN gesture");
        tft.println("2");
        break;

      case GESTURE_LEFT:
        Serial.println("Detected LEFT gesture");
        tft.println("3");
        break;

      case GESTURE_RIGHT:
        Serial.println("Detected RIGHT gesture");
        tft.println("4");
        break;

      default:
        // ignore
        break;
    }
  }
}



