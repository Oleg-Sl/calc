#include "s21_calc.h"

int main() {
  char *tmp = "123.45";
  double d = strtod(tmp, NULL);
  printf("%lf", d);
}