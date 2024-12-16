#include "ui.h"

#ifndef _LED_H
#define _LED_H






#ifdef __cplusplus 
extern "C" {
#endif  //__cplusplus 
void led_off(void);
void led_init();
void led_set(int dut);
#ifdef __cplusplus 
}
#endif  //__cplusplus

#endif