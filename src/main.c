#include <ncurses.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

volatile bool done = FALSE;

void * input( char * ch){
  while(*ch != 27){
    *ch = getch();
  }
  done = TRUE;
  return NULL;
}

void * timer(time_t * t){
  time_t stime, ctime;
  stime = time(NULL);
  while(TRUE){
    ctime = time(NULL);
    *t = ctime - stime;
    sleep(1);
  }
}

int main()
{
  initscr();
  noecho();
  raw();
  curs_set(0);

  int ch = ' ';
  pthread_t iThread;
  pthread_create(&iThread, NULL, input, &ch);

  pthread_t tThread;
  time_t dtime;
  pthread_create(&tThread, NULL, timer, &dtime);

  char * clr[COLS];
  WINDOW * clock;
  clock = newwin(1, 8, 0, COLS - 8);

  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  refresh();

  while(!done){

    wmove(clock, 0, 0);
    wprintw(clock, "        ");
    wmove(clock, 0, 0);
    wprintw(clock, "%ld:%ld:%ld", dtime/(60*60), (dtime/60)%60, dtime%60);
    wrefresh(clock);

    mvprintw(0, 0, "%c", ch);
    mvprintw(3, 0, "%d", tm.tm_mon);
    refresh();
  }

  endwin();
}

