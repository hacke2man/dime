#include "limits.h"
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include "timer.h"

//TODO: refector
//TODO: change how state is stored

volatile bool done = FALSE;
time_t dtime;
long score;
long day;
long position;
FILE * fp;
FILE * lg;

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
  dest[0] = '\0';
  strcpy(dest, itemstart);
  *breakchar = ',';
  return dest;
}

void ReadStats(char * statString)
{
  day = getNum(statString);

  char * next = strchr(statString, ',');
  score = getNum(&next[1]);

  next = strchr(&next[1], ',');
  position = getNum(&next[1]);
}

void WriteStats()
{
  char out[50];
  sprintf(out, "%ld,%ld,%ld,\n", day, score, position);
  fputs(out, lg);
}

int CountLines()
{
  int lineCount = 0;
  char temp[150];
  while(fgets(temp, 150, fp)){ lineCount++; }
  rewind(fp);

  return lineCount;
}

void spit()
{
  char line[50];
  int itemposition = position;

  for(int i = 0; i < itemposition; i++){
    fgets(line, 50, fp);
  }

  printf("%s\nScore:%ld\n", getstring(line), score);
  exit(0);
}

void Done(char * itemname)
{
  char line[50];
  char * name;
  long points = 0;
  char * itemstart;
  char * itemend;
  int i;

  for(i = 0; i < CountLines(); i++){
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

  if(position + 1 < CountLines())
  {
    if(position == i + 1)
      position += 1;
  } else {
    position = 1;
  }
}

void Score()
{
  printf("Score:%ld\n", score);
}

int main(int argc, char * argv[])
{
  char line[50];
  char list[PATH_MAX];
  char log[PATH_MAX];
  char * home = getenv("HOME");

  sprintf(list, "%s/.config/dime/tasklist", home);
  sprintf(log, "%s/.local/share/dime/log", home);
  fp = fopen(list, "r");
  lg = fopen(log, "a+");
  while(fgets(line, 50, lg)){}
  ReadStats(line);

  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  int checkDay = tm.tm_yday;

  if(checkDay !=day)
  {
    day = checkDay;
    position = 1;
    score = 0;
  }

  if(argc == 1)
    spit();

  for(int i = 0; i < argc; i++)
  {
    if(*argv[i] == '-' )
    {
      switch(argv[i][1])
      {
        case 'd':
          Done(argv[i+1]);
          break;
        case 'r':
          score = 0;
          break;
        case 's':
          Score();
          break;
        default:
          break;
      }
      //TODO:add undo
    }
  }

  WriteStats();
  fclose(fp);
  fclose(lg);
}
