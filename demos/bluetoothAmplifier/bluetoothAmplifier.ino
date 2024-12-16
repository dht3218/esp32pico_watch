/*!
 * @file  bluetoothAmplifier.ino
 * @brief  Simple Bluetooth Audio Player
 * @details  When your other Bluetooth devices (e.g. cellphone) is successfully connected to the ESP32 controller that has burnt this sample 
 * @n  and the amplifier has been properly connected to ESP32 through the I2S communication pin,
 * @n  you got a simple Bluetooth speaker, you can hear the music playing in your phone from the speaker connected to the amplifier,
 * @n  and you can get some information about the song currently playing through the Bluetooth AVRCP protocol command.
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license  The MIT License (MIT)
 * @author  [qsjhyy](yihuan.huang@dfrobot.com)
 * @version  V1.0
 * @date  2022-01-24
 * @url  https://github.com/DFRobot/DFRobot_MAX98357A
 */
#include <DFRobot_MAX98357A.h>

DFRobot_MAX98357A amplifier;   // instantiate an object to control the amplifier

void setup(void)
{
  Serial.begin(115200);
  pinMode(20, OUTPUT);
  digitalWrite(20, LOW);
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  /**
   * @brief Init function
   * @param btName - The created Bluetooth device name
   * @param bclk - I2S communication pin number, serial clock (SCK), aka bit clock (BCK)
   * @param lrclk - I2S communication pin number, word select (WS), i.e. command (channel) select, used to switch between left and right channel data
   * @param din - I2S communication pin number, serial data signal (SD), used to transmit audio data in two's complement format
   * @return true on success, false on error
   */
  while( !amplifier.begin(/*btName=*/"bluetoothAmplifier", /*bclk=*/GPIO_NUM_14, /*lrclk=*/GPIO_NUM_2, /*din=*/GPIO_NUM_27) ){
    Serial.println("Initialize failed !");
    delay(3000);
  }
  Serial.println("Initialize succeed!");

}

void loop(void)
{
  String Title, Artist, Album;
  /**
   * @brief Get "metadata" through AVRC command
   * @param type - The type of metadata to be obtained, and the parameters currently supported:
   * @n     ESP_AVRC_MD_ATTR_TITLE   ESP_AVRC_MD_ATTR_ARTIST   ESP_AVRC_MD_ATTR_ALBUM
   * @return The corresponding type of "metadata"
   * @note Return "NULL" if timeout occurs when requesting metadata
   */
  Title = amplifier.getMetadata(ESP_AVRC_MD_ATTR_TITLE);
  if(0 != Title.length()){
    Serial.print("Music title: ");
    Serial.println(Title);
  }
  Artist = amplifier.getMetadata(ESP_AVRC_MD_ATTR_ARTIST);
  if(0 != Artist.length()){
    Serial.print("Music artist: ");
    Serial.println(Artist);
  }
  Album = amplifier.getMetadata(ESP_AVRC_MD_ATTR_ALBUM);
  if(0 != Album.length()){
    Serial.print("Music album: ");
    Serial.println(Album);
  }
  delay(3000);
}
