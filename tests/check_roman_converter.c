#include <stdlib.h>
#include <check.h>
#include "../src/roman_converter.h"

START_TEST(the_glyphs) {
  int arabic = 0;
  arabic = roman_to_int("I");
  ck_assert_int_eq(arabic, 1);

  arabic = roman_to_int("V");
  ck_assert_int_eq(arabic, 5);

  arabic = roman_to_int("X");
  ck_assert_int_eq(arabic, 10);

  arabic = roman_to_int("L");
  ck_assert_int_eq(arabic, 50);

  arabic = roman_to_int("C");
  ck_assert_int_eq(arabic, 100);

  arabic = roman_to_int("D");
  ck_assert_int_eq(arabic, 500);

  arabic = roman_to_int("M");
  ck_assert_int_eq(arabic, 1000);
}
END_TEST

START_TEST(roman_to_arabic) {
  int arabic = 0;
  arabic = roman_to_int("II");
  ck_assert_int_eq(arabic, 2);

  arabic = roman_to_int("MDCLXVI");
  ck_assert_int_eq(arabic, 1666);

  arabic = roman_to_int("IV");
  ck_assert_int_eq(arabic, 4);

  arabic = roman_to_int("CDXLIV");
  ck_assert_int_eq(arabic, 444);

  arabic = roman_to_int("CMXCIX");
  ck_assert_int_eq(arabic, 999);

  arabic = roman_to_int("XIV");
  ck_assert_int_eq(arabic, 14);

  arabic = roman_to_int("LXXIV");
  ck_assert_int_eq(arabic, 74);

  arabic = roman_to_int("MCMLIV");
  ck_assert_int_eq(arabic, 1954);

  arabic = roman_to_int("MCMXC");
  ck_assert_int_eq(arabic, 1990);

  arabic = roman_to_int("MMXIV");
  ck_assert_int_eq(arabic, 2014);
}
END_TEST

START_TEST(can_handle_unconventional_numerals) {
  int arabic = 0;
  arabic = roman_to_int("IIII");
  ck_assert_int_eq(arabic, 4);

  arabic = roman_to_int("CCCCXXXX");
  ck_assert_int_eq(arabic, 440);

  arabic = roman_to_int("IIIIII");
  ck_assert_int_eq(arabic, 6);

  arabic = roman_to_int("XXXXXX");
  ck_assert_int_eq(arabic, 60);

  arabic = roman_to_int("MDCCCCX");
  ck_assert_int_eq(arabic, 1910);

  arabic = roman_to_int("DD");
  ck_assert_int_eq(arabic, 1000);
}
END_TEST

START_TEST(invalid_characters_ignored) {
  int arabic = 0;
  arabic = roman_to_int("V?I");
  ck_assert_int_eq(arabic, 6);

  char just_a_null[] = {'\0'};
  arabic = roman_to_int(just_a_null);
  ck_assert_int_eq(arabic, 0);
}
END_TEST

Suite * roman_converter_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("Roman Converter");

  /* Core test case */
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, the_glyphs);
  tcase_add_test(tc_core, roman_to_arabic);
  tcase_add_test(tc_core, invalid_characters_ignored);
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
