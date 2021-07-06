#include "limits.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include "timer.h"
#include "parse.h"
#include "filefunc.h"
#include "output.h"
#include "queue.h"

task * createtask(char * input, unsigned int p){
  task * out = malloc(sizeof(task));
  out->name = input;
  out->points = p;
  return out;
}

void resetstate(struct queue * queue, FILE * fp)
{
  char line[50];
  char out[150];
  FILE * st = initFile(".local/share/dime/state", "w");

  while(dequeue(queue)){}

  rewind(fp);
  while(fgets(line, 50, fp))
  {
    enqueue(queue, createtask(getstring(line), getNum(&strchr(line, ',')[1])));
  }

  int i = 0;
  do {
    sprintf(out, "%s,%d,\n", getTask(queue)->name, getTask(queue)->points);
    fputs(out, st);
    i++;
  } while(dequeue(queue) && i < 5);
  fclose(st);
}

int main(int argc, char * argv[])
{
  struct queue * queue = createqueue();
  char line[50];
  long score;
  long day;
  FILE * fp = initFile(".config/dime/tasklist", "r");
  FILE * lg = initFile(".local/share/dime/log", "a+");
  FILE * st = initFile(".local/share/dime/state", "r");

  while(fgets(line, 50, st))
  {
    if(strlen(line) > 1)
    {
      enqueue(queue, createtask(getstring(line), getNum(&strchr(line, ',')[1])));
    }
  }

  while(fgets(line, 50, lg)){}
  ReadStats(line, &day, &score);

  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  int checkDay = tm.tm_yday;

  if(checkDay !=day)
  {
    resetstate(queue, fp);
    day = checkDay;
    score = 0;
  }

  if(argc == 1)
    spit(queue, score);

  for(int i = 0; i < argc; i++)
  {
    if(*argv[i] == '-' )
    {
      switch(argv[i][1])
      {
        case 'd':
          Done(queue, &score);
          break;
        case 'r':
          resetstate(queue, fp);
          score = 0;
          break;
        case 's':
          Score(score);
          break;
          break;
        default:
          break;
      }
      //TODO:add undo
    }
  }

  WriteStats(lg, day, score);
  fclose(fp);
  fclose(lg);
  fclose(st);
}
