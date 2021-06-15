#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include "timer.h"

volatile bool done = FALSE;
time_t dtime;
long score;
long position;

long getNum(char * itemstart){
  char * itemend = strchr(itemstart, ',');
  return strtol(itemstart, &itemend, 10);
}

char * getstring(char * itemstart){
  char * breakchar = strchr(itemstart, ',');
  *breakchar = '\0';
  char * dest = malloc(sizeof(char) * (strlen(itemstart) + 1));
  strcpy(dest, itemstart);
  *breakchar = ',';
  return dest;
}

void ReadStats(char * statString){
  position = getNum(statString);

  char * next = strchr(statString, ',');
  score = getNum(statString);
}

void WriteStats(FILE * fp){
  char out[50];
  rewind(fp);
  sprintf(out, "%ld,%ld,\n", position, score);
  fputs(out, fp);
}

void spit()
{
  char line[50];
  FILE * fp = fopen("sup", "r+");
  ReadStats(fgets(line, 50, fp));

  for(int i = 0; i < 1 + position; i++){
    fgets(line, 50, fp);
  }

  position++;
  if(position > 7)
    position = 0;


  printf("%s", getstring(line));
  WriteStats(fp);
}


/* void interface(){ */
/*   initscr(); */
/*   noecho(); */
/*   raw(); */
/*   curs_set(0); */

/*   int ch = ' '; */
/*   pthread_t iThread; */
/*   pthread_create(&iThread, NULL, input, &ch); */

/*   pthread_t tThread; */
/*   pthread_create(&tThread, NULL, timer, &dtime); */

/*   char * clr[COLS]; */
/*   WINDOW * clock; */
/*   clock = newwin(1, 8, 0, COLS - 8); */

/*   time_t t = time(NULL); */
/*   struct tm tm = *localtime(&t); */
/*   refresh(); */

/*   while(!done){ */
/*     wmove(clock, 0, 0); */
/*     wprintw(clock, "        "); */
/*     wmove(clock, 0, 0); */
/*     wprintw(clock, "%ld:%ld:%ld", dtime/(60*60), (dtime/60)%60, dtime%60); */
/*     wrefresh(clock); */

/*     mvprintw(0, 0, "%c", ch); */
/*     mvprintw(3, 0, "%d", tm.tm_mon); */
/*     WINDOW * timerWin; */
/*     timerWin = newwin(1, 8, 0, COLS - 8); */

/*     DispTimer(timerWin, &dtime); */
/*     mvprintw(0,0,"%c",ch); */

/*     refresh(); */
/*   } */

/*   endwin(); */
/* } */

int main(int argc, char * argv[])
{
  if(argc == 1)
    spit();
}
