#include <stdlib.h>
#include <check.h>
#include "../src/roman_converter.h"

START_TEST(roman_to_arabic_glyphs) {
  ck_assert_int_eq(roman_to_int("I"), 1);
  ck_assert_int_eq(roman_to_int("V"), 5);
  ck_assert_int_eq(roman_to_int("X"), 10);
  ck_assert_int_eq(roman_to_int("L"), 50);
  ck_assert_int_eq(roman_to_int("C"), 100);
  ck_assert_int_eq(roman_to_int("D"), 500);
  ck_assert_int_eq(roman_to_int("M"), 1000);
}
END_TEST

START_TEST(roman_to_arabic) {
  ck_assert_int_eq(roman_to_int("II"), 2);
  ck_assert_int_eq(roman_to_int("MDCLXVI"), 1666);
  ck_assert_int_eq(roman_to_int("IV"), 4);
  ck_assert_int_eq(roman_to_int("CDXLIV"), 444);
  ck_assert_int_eq(roman_to_int("CMXCIX"), 999);
  ck_assert_int_eq(roman_to_int("XIV"), 14);
  ck_assert_int_eq(roman_to_int("LXXIV"), 74);
  ck_assert_int_eq(roman_to_int("MCMLIV"), 1954);
  ck_assert_int_eq(roman_to_int("MCMXC"), 1990);
  ck_assert_int_eq(roman_to_int("MMXIV"), 2014);
}
END_TEST

START_TEST(roman_to_arabic_can_handle_unconventional_numerals) {
  ck_assert_int_eq(roman_to_int("IIII"), 4);
  ck_assert_int_eq(roman_to_int("CCCCXXXX"), 440);
  ck_assert_int_eq(roman_to_int("IIIIII"), 6);
  ck_assert_int_eq(roman_to_int("XXXXXX"), 60);
  ck_assert_int_eq(roman_to_int("MDCCCCX"), 1910);
  ck_assert_int_eq(roman_to_int("DD"), 1000);
}
END_TEST

START_TEST(roman_to_arabic_invalid_characters_ignored) {
  ck_assert_int_eq(roman_to_int("V?I"), 6);

  char just_a_null[] = {'\0'};
  ck_assert_int_eq(roman_to_int(just_a_null), 0);
}
END_TEST

void roman_eq(int to_convert, char expected[]) {
  char* arabic = int_to_roman(to_convert);
  ck_assert_str_eq(arabic, expected);
  free(arabic);
}

START_TEST(arabic_to_roman_glyphs) {
  roman_eq(1, "I");
  roman_eq(5, "V");
  roman_eq(10, "X");
  roman_eq(50, "L");
  roman_eq(100, "C");
  roman_eq(500, "D");
  roman_eq(1000, "M");
}
END_TEST

START_TEST(arabic_to_roman) {
  roman_eq(2, "II");
  roman_eq(2, "II");
  roman_eq(16, "XVI");
  roman_eq(4, "IV");
  roman_eq(9, "IX");
  roman_eq(40, "XL");
  roman_eq(90, "XC");
  roman_eq(400, "CD");
  roman_eq(900, "CM");
  roman_eq(14, "XIV");
  roman_eq(74, "LXXIV");
  roman_eq(1954, "MCMLIV");
  roman_eq(1990, "MCMXC");
  roman_eq(2014, "MMXIV");
  roman_eq(-13, "-XIII");
}
END_TEST

Suite * roman_converter_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("Roman Converter");

  /* Core test case */
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, roman_to_arabic_glyphs);
  tcase_add_test(tc_core, roman_to_arabic);
  tcase_add_test(tc_core, roman_to_arabic_can_handle_unconventional_numerals);
  tcase_add_test(tc_core, roman_to_arabic_invalid_characters_ignored);
  tcase_add_test(tc_core, arabic_to_roman_glyphs);
  tcase_add_test(tc_core, arabic_to_roman);
  suite_add_tcase(s, tc_core);

  return s;
}

int failing_tests(Suite* s) {
  int number_failed;
  SRunner *sr;

  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return number_failed;
}

int main(void) {
  Suite *s = roman_converter_suite();
  return (failing_tests(s) == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
