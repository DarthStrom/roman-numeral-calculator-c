#ifndef ROMAN_CALCULATOR_H
#define ROMAN_CALCULATOR_H

#include <string.h>
#include "roman_converter.h"

// Returns a new char* representing the roman numeral of the sum of the roman
// numerals a and b.
// TODO: what happens on invalid input?
char* add_roman(char a[], char b[]);

#endif /* ROMAN_CALCULATOR_H */
