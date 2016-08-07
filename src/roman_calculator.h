#ifndef ROMAN_CALCULATOR_H
#define ROMAN_CALCULATOR_H

#include <string.h>
#include "roman_converter.h"

// Returns a new char* representing the roman numeral of the sum of the roman
// numerals augend and addend.
// TODO: what happens on invalid input?
char* add_roman(char augend[], char addend[]);

// Returns a new char* representing the roman numeral of the difference of the
// roman numerals minuend and subtrahend.
char* subtract_roman(char minuend[], char subtrahend[]);

#endif /* ROMAN_CALCULATOR_H */
