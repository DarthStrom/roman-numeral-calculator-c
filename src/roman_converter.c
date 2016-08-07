#include <assert.h>
#include <stdlib.h>
#include "roman_converter.h"

// private

static const unsigned int ABREVIATION_SIZE = 4;

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

char* int_to_char(int number) {
  char* result = malloc(sizeof(char));
  int base_values[] = { 1000, 500, 100, 50, 10, 5, 1 };
  char glyphs[] = "MDCLXVI";
  int num_glyphs = sizeof(glyphs) - 1;
  assert(sizeof(base_values)/sizeof(int) == num_glyphs);

  int glyph_location = 0;
  int i;
  for(i = 0; i < num_glyphs; i++) {
    while(base_values[i] <= number) {
      number -= base_values[i];
      result = realloc(result, sizeof(result) + sizeof(char));
      result[glyph_location] = glyphs[i];
      glyph_location += 1;
    }
  }
  result[glyph_location] = '\0';

  return result;
}

void insert_expansion(char* destination, char c, unsigned int times, unsigned int* starting_index) {
  unsigned int i;
  for(i = 0; i < times; i++) {
    destination[*starting_index + i] = c;
  }
  *starting_index += times;
}

char* expand_abbreviations(char original[]) {
  unsigned int original_length = strlen(original);
  unsigned int new_length = original_length * 3 + 1;
  char* new = calloc(new_length, sizeof(char));
  unsigned int j = 0;

  unsigned int i;
  for(i = 0; i < original_length; i++) {
    if(original[i] == 'I' && original[i+1] == 'V') {
      insert_expansion(new, 'I', ABREVIATION_SIZE, &j);
      i += 1;
    } else if(original[i] == 'I' && original[i+1] == 'X') {
      insert_expansion(new, 'V', 1, &j);
      insert_expansion(new, 'I', ABREVIATION_SIZE, &j);
      i += 1;
    } else if(original[i] == 'X' && original[i+1] == 'L') {
      insert_expansion(new, 'X', ABREVIATION_SIZE, &j);
      i += 1;
    } else if(original[i] == 'X' && original[i+1] == 'C') {
      insert_expansion(new, 'L', 1, &j);
      insert_expansion(new, 'X', ABREVIATION_SIZE, &j);
      i += 1;
    } else if(original[i] == 'C' && original[i+1] == 'D') {
      insert_expansion(new, 'C', ABREVIATION_SIZE, &j);
      i += 1;
    } else if(original[i] == 'C' && original[i+1] == 'M') {
      insert_expansion(new, 'D', 1, &j);
      insert_expansion(new, 'C', ABREVIATION_SIZE, &j);
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

// public

int roman_to_int(char roman[]) {
  char* expanded = expand_abbreviations(roman);
  int result = tally(expanded);
  free(expanded);

  return result;
}

char* int_to_roman(int arabic) {
  char* result = malloc(sizeof(char) + 1);
  result = int_to_char(arabic);

  return result;
}
