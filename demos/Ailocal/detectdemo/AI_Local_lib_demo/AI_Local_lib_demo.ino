#include "AisassistantLocal.h"

void setup()
{
  pinMode(35, INPUT_PULLUP);
  // put your setup code here, to run once:
  AILocalsetup();
}

void loop()
{
  // put your main code here, to run repeatedly:
  
  if (digitalRead(35) == LOW)
  {
    AILocalsetup();
    delay(1000);
  }
}
