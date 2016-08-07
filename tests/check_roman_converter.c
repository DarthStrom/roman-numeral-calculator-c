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

START_TEST(arabic_to_roman_glyphs) {
  ck_assert_str_eq(int_to_roman(1), "I");
  ck_assert_str_eq(int_to_roman(5), "V");
  ck_assert_str_eq(int_to_roman(10), "X");
  ck_assert_str_eq(int_to_roman(50), "L");
  ck_assert_str_eq(int_to_roman(100), "C");
  ck_assert_str_eq(int_to_roman(500), "D");
  ck_assert_str_eq(int_to_roman(1000), "M");
}
END_TEST

START_TEST(arabic_to_roman) {
  ck_assert_str_eq(int_to_roman(2), "II");
  ck_assert_str_eq(int_to_roman(16), "XVI");
  ck_assert_str_eq(int_to_roman(4), "IV");
  ck_assert_str_eq(int_to_roman(9), "IX");
  ck_assert_str_eq(int_to_roman(40), "XL");
  ck_assert_str_eq(int_to_roman(90), "XC");
  ck_assert_str_eq(int_to_roman(400), "CD");
  ck_assert_str_eq(int_to_roman(900), "CM");
  ck_assert_str_eq(int_to_roman(14), "XIV");
  ck_assert_str_eq(int_to_roman(74), "LXXIV");
  ck_assert_str_eq(int_to_roman(1954), "MCMLIV");
  ck_assert_str_eq(int_to_roman(1990), "MCMXC");
  ck_assert_str_eq(int_to_roman(2014), "MMXIV");

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
