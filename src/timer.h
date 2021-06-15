#ifndef __TIMER_H__
#define __TIMER_H__

#ifdef __cplusplus
extern "C" {
#endif
#include <time.h>
#include <ncurses.h>
#include <unistd.h>

  void * timer(time_t * t);
  void DispTimer(WINDOW * timerWin, time_t * dtime);

#ifdef __cplusplus
}
#endif

#endif
