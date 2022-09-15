#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node_str {
  struct Node_str* next;
  char* str;
} Node_str;

typedef struct Node_double {
  struct Node_double* next;
  double digit;
} Node_double;
