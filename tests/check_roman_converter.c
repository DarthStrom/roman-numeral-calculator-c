#include <stdlib.h>
#include <check.h>
#include "../src/roman_converter.h"

START_TEST(roman_to_arabic) {
  int arabic = roman_to_int("I");
  ck_assert_int_eq(arabic, 1);

  arabic = roman_to_int("II");
  ck_assert_int_eq(arabic, 2);
}
END_TEST

Suite * roman_converter_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("Roman Converter");

  /* Core test case */
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, roman_to_arabic);
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
