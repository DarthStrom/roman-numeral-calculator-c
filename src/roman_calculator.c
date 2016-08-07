#include "roman_calculator.h"

char* add_roman(char a[], char b[]) {
  int x = roman_to_int(a);
  int y = roman_to_int(b);
  int sum = x + y;

  return int_to_roman(sum);
}
