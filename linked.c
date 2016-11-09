#include "linked.h"

int search(struct node *s, int var) {
   //if there is nothing in the list or the end is reached
   if(s == NULL) {
      return 0;
   //if the value has been found
   } else if(s->val == var) {
      return 1;
   //if the value has not been found and there is more list left to search
   } else {
      search(s->next, var);
   }
}

int append(struct node **s, int var) {
   struct node *c, *temp;

   //if the list is empty
   if((*s)->val == NULL) {
      (*s)->val = var;
      (*s)->next = NULL;
      return 0;
   }

   c = (*s);

   while(c->next != NULL) {
      c = c->next;
   }

   temp = malloc(sizeof(struct node));
   temp->val = var;
   temp->next = NULL;

   c->next = temp;

   return 0;
}

int delete(struct node **s, int var) {
   struct node *c, *p;

   //if the value is not in the list
   if(search((*s), var) == 0) {
      return 0;
   }

   c = (*s);

   //find the node to delete
   while(c->val != var && c->next != NULL) {
      p = c;
      c = c->next;
   }
      
   //if the value to delete is the current node
   if(c->val == var) {
      //if the current node is the first node
      if((*s) == c) {
	 (*s) = c->next;
	 free(c);
	 return 0;
      }
      //if the current node is not the first node
      else {
	 p->next = c->next;
	 free(c);
	 return 0;
      }
   }

}

int print(struct node *s) {
   while(s != NULL) {
      printf("%d ->", s->val);
      s = s->next;
   }
   printf("\n");

   return 0;
}
