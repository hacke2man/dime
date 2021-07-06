#include "filefunc.h"
#include "parse.h"

void ReadStats(char * statString, long * day, long * score)
{
  *day = getNum(statString);

  char * next = strchr(statString, ',');
  *score = getNum(&next[1]);
}

void WriteStats(FILE * lg, long day, long score)
{
  char out[50];
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
