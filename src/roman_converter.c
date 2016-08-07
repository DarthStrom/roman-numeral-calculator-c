#include <stdlib.h>
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

char* expand_abbreviations(char original[]) {
  unsigned int original_length = strlen(original);
  unsigned int new_length = original_length * 3 + 1;
  char* new = calloc(new_length, sizeof(char));
  unsigned int j = 0;

  unsigned int i;
  for(i = 0; i < original_length; i++) {
    if(original[i] == 'I' && original[i+1] == 'V') {
      new[j+0] = 'I';
      new[j+1] = 'I';
      new[j+2] = 'I';
      new[j+3] = 'I';
      j += 4;
      i += 1;
    } else {
      new[j] = original[i];
      j += 1;
    }
  }

  return new;
}

int tally(char* expanded) {
  int result = 0;

  unsigned int i;
  for(i = 0; i < strlen(expanded); i++) {
    result += char_to_int(expanded[i]);
  }

  return result;
}

int roman_to_int(char roman[]) {
  char* expanded = expand_abbreviations(roman);
  int result = tally(expanded);
  free(expanded);

  return result;
}
