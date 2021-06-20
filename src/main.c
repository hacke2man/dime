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
long day;

long getNum(char * itemstart)
{
  char * itemend = strchr(itemstart, ',');
  return strtol(itemstart, &itemend, 10);
}

char * getstring(char * itemstart)
{
  char * breakchar = strchr(itemstart, ',');
  *breakchar = '\0';
  char * dest = malloc(sizeof(char) * (strlen(itemstart) + 1));
  strcpy(dest, itemstart);
  *breakchar = ',';
  return dest;
}

void ReadStats(char * statString)
{
  day = getNum(statString);

  char * next = strchr(statString, ',');
  score = getNum(&next[1]);
}

void WriteStats()
{
  FILE * fp = fopen("sup", "r+");
  char out[50];
  rewind(fp);
  sprintf(out, "%ld,%ld,\n", day, score);
  fputs(out, fp);
  fclose(fp);
}

void spit()
{
  char line[50];
  FILE * fp = fopen("sup", "r+");
  int position = rand()%8;

  for(int i = 0; i < 1 + position; i++){
    fgets(line, 50, fp);
  }
  fclose(fp);

  time_t seed;
  srand(time(&seed));

  printf("%s", getstring(line));
  WriteStats();
  exit(0);
}

void Done(char * itemname)
{
  FILE * fp = fopen("sup", "r+");
  char line[50];
  char * name;
  long points = 0;
  char * itemstart;
  char * itemend;

  for(int i = 0; i < 1 + 8; i++){
    fgets(line, 50, fp);
    name = getstring(line);
    if(strcmp(itemname, name) == 0)
    {
      itemstart = strchr(line, ',');
      itemend = strchr(itemstart, ',');
      points = strtol(&itemstart[1], &itemend, 10);
      score = score + points;
      printf("score: %ld\n", score);
      break;
    }
  }

  WriteStats();
  fclose(fp);
}

void Reset()
{
  FILE * fp = fopen("sup", "r+");
  score = 0;
  WriteStats();
  fclose(fp);
}

int main(int argc, char * argv[])
{
  char line[50];
  /* TODO:use getenv("HOME")/.config/dime/tasklist */
  FILE * fp = fopen("sup", "r+");
  fgets(line, 50, fp);
  ReadStats(line);
  fclose(fp);

  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  int checkDay = tm.tm_yday;

  if(checkDay !=day)
  {
    Reset();
    day = checkDay;
  }

  if(argc == 1)
    spit();

  for(int i = 0; i < argc; i++)
  {
    if(*argv[i] == '-' )
    {
      if(argv[i][1] == 'd')
        Done(argv[i+1]);
      else if (argv[i][1] == 'r')
       Reset();
      //TODO:add undo
    }
  }
  fclose(fp);
}
