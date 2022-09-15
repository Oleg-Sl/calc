#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"


Node* initStack() {
    return NULL;
}

void push(Node** top, char* str) {
  Node* tmp = (Node*)malloc(sizeof(Node));
  tmp->next = *top;
  tmp->str = str;
  *top = tmp;
}

char* pop(Node** top) {
  char* str = NULL;
  if (*top != NULL) {
    Node* tmp = *top;
    // str = realloc(str, sizeof(tmp->str));
    str = tmp->str;
    *top = tmp->next;
    free(tmp);
  }
  return str;
}

void removeStack(Node** top) {
  while (*top != NULL) {
    Node* tmp = *top;
    *top = tmp->next;
    free(tmp);
  }
}

void printStack(Node* top) {
  Node* tmp = top;
  while (tmp != NULL) {
    printf("%s ", tmp->str);
    tmp = tmp->next;
  }
  printf("\n");
}

char* peek(Node* top) {
  char* str = NULL;
  if (top)
    str = top->str;

  return str;
}

