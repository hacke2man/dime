#ifndef __FILEFFUNC_H__
#define __FILEFFUNC_H__

#ifdef __cplusplus
extern "C" {
#endif
#include <stdio.h>
#include "linux/limits.h"

void ReadStats(char * statString, long * day, long * score);
void WriteStats(FILE * lg, long day, long score);
int CountLines(FILE * fp);
FILE * initFile(char * path, char * opt);

#ifdef __cplusplus
}
#endif

#endif
