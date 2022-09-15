#include "s21_calc.h"


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

int get_top_priority(Node* top) {
  int res = 0;
  if (peek(top)) {
    res = get_c_priority(top->str);
  }
  return res;
}

char* str_push(char* str, const char c) {
  if (str == NULL) {
    str = calloc(2, sizeof(char));
    str[0] = c;
  } else {
    int len = strlen(str);
    str = realloc(str, len);
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

void digit_parcing(Node** numbers, Node** signs, char* exp, int* i, int uno,
                   int* m_flag) {
  int flag = 0;
  char* res = calloc(2, sizeof(char));
  if (uno && (exp[*i] == '-' || exp[*i] == '+')) {
    char* tmp = calloc(2, sizeof(char));
    tmp[0] = exp[*i];
    push(signs, tmp);
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
  push(numbers, res);
  *i -= 1;
}

void func_parcing(Node** func, char* str, int* i, int* uno, int* flag) {
  char* res = NULL;
  if (uno && (str[*i] == '-' || str[*i] == '+')) {
    char* tmp = calloc(2, sizeof(char));
    tmp[0] = str[*i];
    push(func, tmp);
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
  push(func, res);
}

void calculation(Node** numbers, char* operator) {
  double num2 = strtod(pop(numbers), NULL);
  double num1 = strtod(pop(numbers), NULL);
  double res = 0;
  printf("OPERATOR = %s\n", operator);
  switch (operator[0]) {
    case '-':
      res = num1 - num2;
      printf("%lf", res);
      break;
    case '+':
    case '*':
    case '/':
    case '^':
    case 'm':
      break;
  }
}

void operator_parcing(Node** numbers, Node** operators, char* str, int* i,
                      int* uno, int* flag) {
  char* tmp = calloc(2, sizeof(char));
  if (*uno) {
    if (str[*i] == '-') {
      char c = '~';
      push(operators, &c);
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
        if (!peek(*operators) ||
            get_top_priority(*operators) >= get_c_priority(&str[*i])) {
          push(operators, tmp);
        } else {
          calculation(numbers, tmp);
        }
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
  Node* numbers = init();
  Node* signs = init();
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
  print_list(signs);
  while (signs != NULL) {
    char* op = pop(&signs);
    if (op[0] == '~') {
      double tmp = strtod(pop(&numbers), NULL);
      tmp *= -1;
      char* res = NULL;
      sprintf(res, "%lf", tmp);
      push(&numbers, op);
      printf("%s", res);
    } else {
      calculation(&numbers, op);
    }
  }
  print_list(numbers);
  free(numbers);
  free(signs);
  return flag;
}

int main(void) {
  char* str = str_input();
  if (parcing(str)) {
  } else {
    printf("Error in the expression");
  }
  free(str);
}
