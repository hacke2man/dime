#include "parse.h"

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

