#include "roman_converter.h"

int char_to_int(char c) {
  if(c == 'I') {
    return 1;
  } else if(c == 'V') {
    return 5;
  } else if(c == 'X') {
    return 10;
  } else if(c == 'L') {
    return 50;
  } else if(c == 'C') {
    return 100;
  } else if(c == 'D') {
    return 500;
  } else if(c == 'M') {
    return 1000;
  }

  return 0;
}

int roman_to_int(char roman[]) {
  int result = 0;

  unsigned int i;
  for(i = 0; i < strlen(roman); i++) {
    result += char_to_int(roman[i]);
  }

  return result;
}
