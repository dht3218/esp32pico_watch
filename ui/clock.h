#include "ui.h"

#ifndef _CLOCK_H
#define _CLOCK_H





#define RXD2 19
#define TXD2 21
#ifdef __cplusplus
extern "C" {
#endif  //__cplusplus
void getDc(int* Y, int* M, int* D);
  const char* getTc(int* H, int* M, int* S);
  void getT4G();
  void RtcSetup();
  void RtcSetup0();
  void RtcgetTwifi();
  void Rtctask(void* arg);
  void Rtctaskcreate();
  void Rtctaskdelete();
  void RtcSetTime(int Hour0, int Hour1, int Min0, int Min1);

#ifdef __cplusplus
}
#endif  //__cplusplus

#endif