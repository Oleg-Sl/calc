#include "queue.h"

Node_double* init_d() { return NULL; }

Node_str* init_s() { return NULL; }

void print_list(Node_str* top_s, Node_double* top_d) {
  if (top_d == NULL) {
    while (top_s != NULL) {
      printf("%s ", top_s->str);
      top_s = top_s->next;
    }
    printf("\n");
  } else if (top_s == NULL) {
    while (top_d != NULL) {
      printf("%lf ", top_d->digit);
      top_d = top_d->next;
    }
    printf("\n");
  }
}

void push(Node_str** top_s, char* str, Node_double** top_d, double digit) {
  if (top_d == NULL) {
    Node_str* tmp = (Node_str*)malloc(sizeof(Node_str));
    tmp->next = *top_s;
    tmp->str = str;
    *top_s = tmp;
  } else if (top_s == NULL) {
    Node_double* tmp = (Node_double*)malloc(sizeof(Node_double));
    tmp->next = *top_d;
    tmp->digit = digit;
    *top_d = tmp;
  }
}

void* pop(Node_str** top_s, Node_double** top_d) {
  void* res = NULL;
  if (top_d == NULL) {
    if (*top_s != NULL) {
      Node_str* tmp = *top_s;
      res = (char*)tmp->str;
      *top_s = tmp->next;
      free(tmp);
    }
  } else if (top_s == NULL) {
    if (*top_d != NULL) {
      Node_double* tmp = *top_d;
      res = &tmp->digit;
      *top_d = tmp->next;
      free(tmp);
    }
  }
  return res;
}

void removeList(Node_str** top_s, Node_double** top_d) {
  if (top_d == NULL) {
    while (*top_s != NULL) {
      Node_str* tmp = *top_s;
      *top_s = tmp->next;
      free(tmp->str);
      free(tmp);
    }
  } else if (top_s == NULL) {
    while (*top_d != NULL) {
      Node_double* tmp = *top_d;
      *top_d = tmp->next;
      free(tmp);
    }
  }
}

int get_c_priority(char* str) {
  int priority = 0;
  if (str[0] == '-' || str[0] == '+') {
    priority = 1;
  } else if (str[0] == '*' || str[0] == '/' || str[0] == 'm') {
    priority = 2;
  } else if (str[0] == '(') {
    priority = 4;
  } else if (str[0] == ')') {
    priority = 5;
  } else {
    priority = 3;
  }
  return priority;
}

int get_top_str_priority(Node_str* top) {
  while (top->next != NULL) {
    top = top->next;
  }
  return get_c_priority(top->str);
}

char* str_push(char* str, const char c) {
  if (str == NULL) {
    str = calloc(2, sizeof(char));
    str[0] = c;
  } else {
    int len = strlen(str);
    str = realloc(str, (len + 1) * sizeof(char));
    str[len] = c;
  }
  return str;
}

char* str_input() {
  char* res = NULL;
  char c;
  while ((c = getchar()) != '\0' && c != '\n') {
    res = str_push(res, c);
  }
  return res;
}

void calculation(Node_double** numbers, char* operator) {
  double dig2 = *(double*)pop(NULL, numbers);
  double dig1 = *(double*)pop(NULL, numbers);
  double res = 0;
  switch (operator[0]) {
    case '-':
      res = dig1 - dig2;
      push(NULL, NULL, numbers, res);
    case '+':
    case '*':
    case '/':
    case '^':
    case 'm':
      break;
  }
}

void digit_parcing(Node_double** numbers, Node_str** signs, char* exp, int* i,
                   int uno, int* m_flag) {
  int flag = 0;
  char* res = calloc(2, sizeof(char));
  if (uno && (exp[*i] == '-' || exp[*i] == '+')) {
    char* tmp = calloc(2, sizeof(char));
    tmp[0] = exp[*i];
    push(signs, tmp, NULL, 0);
    *i += 1;
  }
  for (int j = 0; (exp[*i] >= '0' && exp[*i] <= '9') || exp[*i] == '.';
       j++, *i += 1) {
    res = realloc(res, (sizeof(res) + 1));
    res[j] = exp[*i];
    if (!flag && exp[*i] == '.') {
      flag++;
    }
    if (flag > 1) {
      *m_flag = 0;
      break;
    }
  }
  push(NULL, NULL, numbers, strtod(res, NULL));
  *i -= 1;
}

void func_parcing(Node_str** func, char* str, int* i, int* uno, int* flag) {
  char* res = NULL;
  if (uno && (str[*i] == '-' || str[*i] == '+')) {
    char* tmp = calloc(2, sizeof(char));
    tmp[0] = str[*i];
    push(func, tmp, NULL, 0);
    *i += 1;
  }
  if (!strncmp(&str[*i], "acos", 4)) {
    *i += 3;
    res = realloc(res, (sizeof(char) + 4));
    strcpy(res, "acos");
  } else if (!strncmp(&str[*i], "asin", 4)) {
    *i += 3;
    res = realloc(res, (sizeof(char) + 4));
    strcpy(res, "asin");
  } else if (!strncmp(&str[*i], "atan", 4)) {
    *i += 3;
    res = realloc(res, (sizeof(char) + 4));
    strcpy(res, "atan");
  } else if (!strncmp(&str[*i], "sqrt", 4)) {
    *i += 3;
    res = realloc(res, (sizeof(char) + 4));
    strcpy(res, "sqrt");
  } else if (!strncmp(&str[*i], "cos", 3)) {
    *i += 2;
    res = realloc(res, (sizeof(char) + 3));
    strcpy(res, "cos");
  } else if (!strncmp(&str[*i], "sin", 3)) {
    *i += 2;
    res = realloc(res, (sizeof(char) + 3));
    strcpy(res, "sin");
  } else if (!strncmp(&str[*i], "log", 3)) {
    *i += 2;
    res = realloc(res, (sizeof(char) + 3));
    strcpy(res, "log");
  } else if (!strncmp(&str[*i], "mod", 3)) {
    *i += 2;
    res = realloc(res, (sizeof(char) + 3));
    strcpy(res, "mod");
  } else if (!strncmp(&str[*i], "tan", 3)) {
    *i += 2;
    res = realloc(res, (sizeof(char) + 3));
    strcpy(res, "tan");
  } else if (!strncmp(&str[*i], "ln", 2)) {
    *i += 1;
    res = realloc(res, (sizeof(char) + 2));
    strcpy(res, "ln");
  } else {
    *flag = 0;
  }
  *uno = 0;
  push(func, res, NULL, 0);
}

void operator_parcing(Node_double** numbers, Node_str** operators, char* str,
                      int* i, int* uno, int* flag) {
  char* tmp = calloc(2, sizeof(char));
  if (*uno) {
    if (str[*i + 1] >= '0' && str[*i + 1] <= '9') {
      digit_parcing(numbers, operators, str, i, *uno, flag);
    } else {
      func_parcing(operators, str, i, uno, flag);
    }
  } else {
    tmp[0] = str[*i];
    switch (tmp[0]) {
      case '-':
      case '+':
      case '*':
      case '/':
      case '^':
      case 'm':
      case '(':
        printf("AAA");
        if (get_top_str_priority(*operators) <= get_c_priority(&str[*i]))
          push(operators, tmp, NULL, 0);
        else
          calculation(numbers, tmp);
        *uno = 0;
        break;
      case ')':
        *uno = 1;
        break;
      default:
        break;
    }
  }
}

int parcing(char* str) {
  Node_double* numbers = init_d();
  Node_str* signs = init_s();
  int flag = 1, uno = 1;
  for (int i = 0; str[i] && flag; i++) {
    if (str[i] >= '0' && str[i] <= '9') {
      uno = 0;
      digit_parcing(&numbers, &signs, str, &i, uno, &flag);
    } else if (str[i] == '-' || str[i] == '+' || str[i] == '*' ||
               str[i] == '/' || str[i] == '^' || str[i] == 'm' ||
               str[i] == '(' || str[i] == ')') {
      operator_parcing(&numbers, &signs, str, &i, &uno, &flag);
    } else if (str[i] == 'c' || str[i] == 's' || str[i] == 't' ||
               str[i] == 'a' || str[i] == 'l') {
      func_parcing(&signs, str, &i, &uno, &flag);
    } else {
      flag = 0;
      break;
    }
  }
  print_list(NULL, numbers);
  print_list(signs, NULL);
  free(numbers);
  free(signs);
  return flag;
}

int main(void) {
  // char* str = str_input();
  char* str = str_input();
  if (parcing(str)) {
  } else {
    printf("Error in the expression");
  }
  // printf("STR = %s", str);
  free(str);

  // push(&top, "1");
  // push(&top, "2");
  // push(&top, "3");
  // push(&top, "4");
  // printf("pop = %s", pop(&top));
  // printf("\n");
  // push(&top, "5");
  // print_list(top);
  // removeList(&top);
  // print_list(top);

  return 0;
}
