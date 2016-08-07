#include <stdlib.h>
#include <check.h>
#include "../src/roman_calculator.h"

START_TEST(addition_empty_strings_count_as_zero) {
  ck_assert_str_eq(add_roman("", ""), "");
  ck_assert_str_eq(add_roman("I", ""), "I");
  ck_assert_str_eq(add_roman("", "II"), "II");
}
END_TEST

START_TEST(addition) {
  ck_assert_str_eq(add_roman("I", "I"), "II");
  ck_assert_str_eq(add_roman("I", "II"), "III");
  ck_assert_str_eq(add_roman("II", "II"), "IV");
  ck_assert_str_eq(add_roman("XX", "II"), "XXII");
  ck_assert_str_eq(add_roman("XIV", "LX"), "LXXIV");
  ck_assert_str_eq(add_roman("D", "D"), "M");
}
END_TEST

Suite * roman_calculator_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("Roman Calculator");

  /* Core test case */
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, addition_empty_strings_count_as_zero);
  tcase_add_test(tc_core, addition);
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
  Suite* s = roman_calculator_suite();
  return (failing_tests(s) == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
