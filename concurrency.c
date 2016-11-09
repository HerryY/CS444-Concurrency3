#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include "linked.h"

int searcher;

struct args {
   int command;
   int value;
   struct node *head;
   sem_t *inserter;
   sem_t *deleter;
};

void exec(void *b) {
   int c, v, test;
   struct node *s;
   struct args *a;
   a = b;

   s = (*a).head;
   c = (*a).command;
   v = (*a).value;

   switch(c) {
      case 0:
	 sem_wait((*a).inserter);
	 sem_wait((*a).deleter);
	 append(&s, v);
	 print((*a).head);
	 sem_post((*a).deleter);
	 sem_post((*a).inserter);
	 break;
      case 1:
	 searcher++;
	 search(s, v);
	 print((*a).head);
	 searcher--;
	 break;
      case 2:
	 while(searcher != 0) {
	 }
	 sem_wait((*a).deleter);
	 sem_wait((*a).inserter);
	 delete(&s, v);
	 print((*a).head);
	 sem_post((*a).inserter);
	 sem_post((*a).deleter);
	 break;
   }
}

int main (void) {
   struct node *head = malloc(sizeof(struct node));
   struct args *arguments;
   sem_t inserter, deleter;

   //init head
   head->val = NULL;
   head->next = NULL;

   //init the semaphores
   sem_init(&inserter, 0, 1);
   sem_init(&deleter, 0, 1);
   searcher = 0;

   pthread_t threads[9];
   int rc;
   long t;

   int commands[9] = {0, 0, 0, 0, 1, 1, 1, 2, 2};
   int values[9] = {4, 1, 8, 5, 90, 1, 4, 4, 5};


   for(t=0; t<9; t++) {
      arguments = malloc(sizeof(struct args));
      //point to the semaphores from the struct
      arguments->head = head;
      arguments->inserter = &inserter;
      arguments->deleter = &deleter;
      arguments->command = commands[t];
      arguments->value = values[t];

      printf("Creating Thread %ld\n", t);
      rc = pthread_create(&threads[t], NULL, exec, (void *)arguments);
      if(rc) {
	 printf("ERROR: return code from pthread_create() is %d\n", rc);
	 exit(-1);
      }
   }
   print(head);

   pthread_exit(NULL);

   return 0;
}
