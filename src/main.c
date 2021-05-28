#include <ncurses.h>
#include <pthread.h>
#include <time.h>

void * sup(){
  mvprintw(2, 0, "sup");
  return NULL;
}

int main()
{
  initscr();
  noecho();
  raw();

  pthread_t thread;
  pthread_create(&thread, NULL, sup, NULL);

  time_t stime, ctime, dtime;
  stime = time(NULL);
  while(TRUE){
    ctime = time(NULL);
    dtime = ctime - stime;
    mvprintw(0,0,"%ld", dtime);
    refresh();
    if(dtime == 10)
      break;
  }

  endwin();
}

