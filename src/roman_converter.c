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

void insert_expansion(char* destination, char c, unsigned int starting_index) {
  destination[starting_index+0] = c;
  destination[starting_index+1] = c;
  destination[starting_index+2] = c;
  destination[starting_index+3] = c;
}

char* expand_abbreviations(char original[]) {
  unsigned int original_length = strlen(original);
  unsigned int new_length = original_length * 3 + 1;
  char* new = calloc(new_length, sizeof(char));
  unsigned int j = 0;

  unsigned int i;
  for(i = 0; i < original_length; i++) {
    if(original[i] == 'I' && original[i+1] == 'V') {
      insert_expansion(new, 'I', j);
      j += 4;
      i += 1;
    } else if(original[i] == 'X' && original[i+1] == 'L') {
      insert_expansion(new, 'X', j);
      j += 4;
      i += 1;
    } else if(original[i] == 'C' && original[i+1] == 'D') {
      insert_expansion(new, 'C', j);
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
