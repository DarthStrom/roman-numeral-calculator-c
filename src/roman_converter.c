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
  char* result = malloc(sizeof(char) * 15);
  int base_values[] = { 1000, 500, 100, 50, 10, 5, 1 };
  char glyphs[] = "MDCLXVI";
  int num_glyphs = strlen(glyphs);
  assert(sizeof(base_values)/sizeof(int) == num_glyphs);

  int glyph_location = 0;
  int i;
  for(i = 0; i < num_glyphs; i++) {
    while(base_values[i] <= number) {
      number -= base_values[i];
      result[glyph_location] = glyphs[i];
      glyph_location += 1;
    }
  }
  result[glyph_location] = '\0';

  return result;
}

void insert_expansion(
  char* destination,
  char c,
  unsigned int times,
  unsigned int* starting_index)
{
  unsigned int i;
  for(i = 0; i < times; i++) {
    destination[*starting_index + i] = c;
  }
  *starting_index += times;
}

char* expand_abbreviations(char original[]) {
  unsigned int original_length = strlen(original);
  unsigned int expanded_length = original_length * 3 + 1;
  char* expanded = calloc(expanded_length, sizeof(char));
  unsigned int j = 0;

  unsigned int i;
  for(i = 0; i < original_length; i++) {
    if(original[i] == 'I' && original[i+1] == 'V') {
      insert_expansion(expanded, 'I', ABREVIATION_SIZE, &j);
      i += 1;
    } else if(original[i] == 'I' && original[i+1] == 'X') {
      insert_expansion(expanded, 'V', 1, &j);
      insert_expansion(expanded, 'I', ABREVIATION_SIZE, &j);
      i += 1;
    } else if(original[i] == 'X' && original[i+1] == 'L') {
      insert_expansion(expanded, 'X', ABREVIATION_SIZE, &j);
      i += 1;
    } else if(original[i] == 'X' && original[i+1] == 'C') {
      insert_expansion(expanded, 'L', 1, &j);
      insert_expansion(expanded, 'X', ABREVIATION_SIZE, &j);
      i += 1;
    } else if(original[i] == 'C' && original[i+1] == 'D') {
      insert_expansion(expanded, 'C', ABREVIATION_SIZE, &j);
      i += 1;
    } else if(original[i] == 'C' && original[i+1] == 'M') {
      insert_expansion(expanded, 'D', 1, &j);
      insert_expansion(expanded, 'C', ABREVIATION_SIZE, &j);
      i += 1;
    } else {
      expanded[j] = original[i];
      j += 1;
    }
  }

  return expanded;
}

void insert_abbreviation(
  char* destination,
  char* abbreviation,
  unsigned int* starting_index)
{
  unsigned int abbreviation_length = strlen(abbreviation);
  unsigned int i;
  for(i = 0; i < abbreviation_length; i++) {
    destination[*starting_index + i] = abbreviation[i];
  }
  *starting_index += abbreviation_length;
}

int is_shortenable_sequence(char* expanded, unsigned int* at, char* sequence) {
  int length = strlen(sequence);
  unsigned int i;
  for(i = 0; i < strlen(sequence); i++) {
    if(expanded[*at+i] != sequence[i]) { return 0; }
  }
  *at += length - 1;
  return 1;
}

char* abbreviate(char original[]) {
  unsigned int original_length = strlen(original);
  char* abbreviated = calloc(original_length + 1, sizeof(char));
  unsigned int j = 0;

  unsigned int i;
  for(i = 0; i < original_length; i++) {
    if(is_shortenable_sequence(original, &i, "DCCCC")) {
      insert_abbreviation(abbreviated, "CM", &j);
    } else if(is_shortenable_sequence(original, &i, "CCCC")) {
      insert_abbreviation(abbreviated, "CD", &j);
    } else if(is_shortenable_sequence(original, &i, "LXXXX")) {
      insert_abbreviation(abbreviated, "XC", &j);
    } else if(is_shortenable_sequence(original, &i, "XXXX")) {
      insert_abbreviation(abbreviated, "XL", &j);
    } else if(is_shortenable_sequence(original, &i, "VIIII")) {
      insert_abbreviation(abbreviated, "IX", &j);
    } else if(is_shortenable_sequence(original, &i, "IIII")) {
      insert_abbreviation(abbreviated, "IV", &j);
    } else {
      abbreviated[j] = original[i];
      j += 1;
    }
  }

  return abbreviated;
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
  char* prefix = arabic < 0 ? "-" : "";
  char* expanded = int_to_char(abs(arabic));
  char* postfix = abbreviate(expanded);
  char* result = malloc(sizeof(prefix) + sizeof(postfix));
  strcpy(result, prefix);
  strcat(result, postfix);
  free(expanded);
  free(postfix);

  return result;
}
