#include "roman_calculator.h"

char* add_roman(char augend[], char addend[]) {
  int x = roman_to_int(augend);
  int y = roman_to_int(addend);
  int sum = x + y;

  return int_to_roman(sum);
}

char* subtract_roman(char minuend[], char subtrahend[]) {
  int x = roman_to_int(minuend);
  int y = roman_to_int(subtrahend);
  int difference = x - y;

  return int_to_roman(difference);
}
