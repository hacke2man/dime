#ifndef __PARSE_H__
#define __PARSE_H__

#ifdef __cplusplus
extern "C" {
#endif
#include <string.h>
#include <stdlib.h>

long getNum(char * itemstart);
char * getstring(char * itemstart);

#ifdef __cplusplus
}
#endif

#endif
