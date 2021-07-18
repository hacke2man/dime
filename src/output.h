#ifndef __OUTPUT_H__
#define __OUTPUT_H__

#ifdef __cplusplus
extern "C" {
#endif
#include <stdio.h>
#include "queue.h"

void spit(struct queue * queue, long score);
void Score();
void Done(struct queue * q, long * score);
void Miss(struct queue * q);

#ifdef __cplusplus
}
#endif

#endif
