#include "output.h"
#include "filefunc.h"
#include "parse.h"
#include <stdio.h>

void spit(struct queue * queue, long score)
{
  if(queue->head != NULL)
    printf("%s:%ld", getTask(queue)->name, score);
}

void Done(struct queue * q, long * score)
{
  *score = *score + getTask(q)->points;
  dequeue(q);
  char out[150];
  FILE * st = initFile(".local/share/dime/state", "w");

  do {
    sprintf(out, "%s,%d,\n", getTask(q)->name, getTask(q)->points);
    fputs(out, st);
  } while(dequeue(q));

  fclose(st);
}

void Miss(struct queue * q) {
  dequeue(q);
  char out[150];
  FILE * st = initFile(".local/share/dime/state", "w");

  do {
    sprintf(out, "%s,0,\n", getTask(q)->name);
    fputs(out, st);
  } while(dequeue(q));

  fclose(st);
}

void Score(long score)
{
  printf("Score:%ld\n", score);
}

