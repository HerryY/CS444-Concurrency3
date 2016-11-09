#include <stdlib.h>
#include <stdio.h>

struct node {
   int val;
   struct node *next;
};

//search
int search(struct node *, int);
//insert
int append(struct node **, int);
//delete
int delete(struct node **, int);
//print
int print(struct node *);
