#include "ui.h"

#ifndef _CLOCK_H
#define _CLOCK_H





#define RXD2 19
#define TXD2 21
#ifdef __cplusplus
extern "C" {
#endif  //__cplusplus
  extern int clockflag;
  void getDc(int* Y, int* M, int* D);
  const char* getTc(int* H, int* M, int* S);
  void gettimeC(int hour, int min, int alarmnum);
  void getT4G();
  void RtcSetup();
  void RtcSetup0();
  void RtcgetTwifi();
  void Rtctask(void* arg);
  void Rtctaskcreate();
  void Rtctaskdelete();
  void RtcSetTime(int Hour0, int Hour1, int Min0, int Min1);
  bool isAlarmedcheck();
  void alarmmusic();
  void setAlarm();
  void getalarmall(int* hour1, int* min1, int* hour2, int* min2, int* hour3, int* min3);
  int alarmumget();
void setTimechar(int timeset,int num);
  void addAlarm(int alarmIndex);
  void removeAlarm(int alarmIndex);
#ifdef __cplusplus
}
#endif  //__cplusplus

#endif