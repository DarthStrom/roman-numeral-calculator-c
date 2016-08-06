#include <assert.h>
#include "roman_calculator.h"

char* add_roman(char a[], char b[]) {
  char* result = malloc(strlen(a) + strlen(b) + 1);
  assert(result != NULL);
  strcpy(result, a);
  strcat(result, b);
  return result;
}
