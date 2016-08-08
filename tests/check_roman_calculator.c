#include <stdlib.h>
#include <check.h>
#include "../src/roman_calculator.h"

void add_eq(char augend[], char addend[], char expected_sum[]) {
  char* actual_sum = add_roman(augend, addend);
  ck_assert_str_eq(actual_sum, expected_sum);
  free(actual_sum);
}

START_TEST(addition_empty_strings_count_as_zero) {
  add_eq("", "", "");
  add_eq("I", "", "I");
  add_eq("", "II", "II");
}
END_TEST

START_TEST(addition) {
  add_eq("I", "I", "II");
  add_eq("I", "II", "III");
  add_eq("II", "II", "IV");
  add_eq("XX", "II", "XXII");
  add_eq("XIV", "LX", "LXXIV");
  add_eq("D", "D", "M");
}
END_TEST

void subtract_eq(char minuend[], char subtrahend[], char expected_difference[]) {
  char* actual_difference = subtract_roman(minuend, subtrahend);
  ck_assert_str_eq(actual_difference, expected_difference);
  free(actual_difference);
}

START_TEST(subtraction) {
  subtract_eq("", "", "");
  subtract_eq("I", "", "I");
  subtract_eq("II", "", "II");
  subtract_eq("I", "I", "");
  subtract_eq("II", "I", "I");
  subtract_eq("II", "II", "");
  subtract_eq("XX", "II", "XVIII");
  subtract_eq("LX", "XIV", "XLVI");
  subtract_eq("M", "D", "D");
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
  tcase_add_test(tc_core, subtraction);
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
