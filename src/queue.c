#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

struct queue * createqueue()
{
  struct queue * newqueue = malloc(sizeof(struct queue));
  newqueue->head = NULL;
  newqueue->tail = NULL;

  return newqueue;
}

int dequeue(struct queue * queue)
{
  struct node * tmp;
  if(queue->head == queue->tail)
  {
      tmp = queue->head;
      queue->head = NULL;
      queue->tail = NULL;
      free(tmp);
      return 0;
  } else
  {
      tmp = queue->head;
      queue->head = queue->head->next;
      free(tmp);
      return 1;
  }
}

void enqueue(struct queue * queue, task * task)
{
  struct node * newnode = malloc(sizeof(struct node));
  newnode->content = task;

  if(queue->head == NULL)
  {
      queue->head = newnode;
      queue->tail = newnode;
  } else
  {
      queue->tail->next = newnode;
      queue->tail = newnode;
  }
}

task * getTask(struct queue * queue)
{
  return queue->head->content;
}
