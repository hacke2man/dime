#include "filefunc.h"
#include "parse.h"
#include <stdio.h>
#include <stdlib.h>

void ReadStats(char * statString, long * day, long * score)
{
  *day = getNum(statString);

  char * next = strchr(statString, ',');
  *score = getNum(&next[1]);
}

void WriteStats(FILE * lg, long day, long score)
{
  char out[50];
  rewind(lg);

  int pos = 0;
  while(fgets(out, 50, lg))
    pos++;

  char * itemend = strchr(out, ',');
  if(strtol(out, &itemend, 10) == day)
  {
    rewind(lg);
    for(int i = 0; i < pos - 1; i++)
    {
      fgets(out, 50, lg);
    }
  }
  sprintf(out, "%ld,%ld,\n", day, score);
  fputs(out, lg);
}

int CountLines(FILE * fp)
{
  int lineCount = 0;
  char temp[150];
  while(fgets(temp, 150, fp)){ lineCount++; }
  rewind(fp);

  return lineCount;
}

FILE * initFile(char * path, char * opt)
{
  char * home = getenv("HOME");
  char * temp = malloc(sizeof(char) * PATH_MAX);
  sprintf(temp, "%s/%s", home, path);
  FILE * file = fopen(temp, opt);

  return file;
}
