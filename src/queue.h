#ifndef __STACK_H__
#define __STACK_H__

#ifdef __cplusplus
extern "C" {
#endif

struct task {
  unsigned int points;
  char * name;
};
typedef struct task task;

struct node {
  task * content;
  struct node * next;
};

struct queue {
  struct node * head;
  struct node * tail;
};



struct queue * createqueue();
int dequeue(struct queue * queue);
void enqueue(struct queue * queue, task * task);
task * getTask(struct queue * queue);


#ifdef __cplusplus
}
#endif

#endif
