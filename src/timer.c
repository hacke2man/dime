#include "timer.h"

void * timer(time_t * t){
  time_t stime, ctime;
  stime = time(NULL);
  while(TRUE){
    ctime = time(NULL);
    *t = ctime - stime;
    sleep(1);
  }
  return NULL;
}

void DispTimer(WINDOW * timerWin, time_t * dtime)
{
    wmove(timerWin, 0, 0);
    wprintw(timerWin, "        ");
    wmove(timerWin, 0, 0);
    wprintw(timerWin, "%ld:%ld:%ld", *dtime/(60*60),(*dtime/60)%60, *dtime%60);
    wrefresh(timerWin);
}
