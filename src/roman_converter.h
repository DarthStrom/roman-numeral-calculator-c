#ifndef ROMAN_CONVERTER_H
#define ROMAN_CONVERTER_H

#include <string.h>

// Returns the integer representation of the roman numeral sent in.
int roman_to_int(char roman[]);

// Returns a roman numeral representing the integer sent in.
char* int_to_roman(int arabic);

#endif /* ROMAN_CONVERTER_H */
