#include <stdlib.h>
#include <check.h>
#include "../src/roman_calculator.h"

START_TEST(empty_strings_count_as_zero) {
  char* sum = add_roman("", "");
  ck_assert_str_eq(sum, "");
  free(sum);

  sum = add_roman("I", "");
  ck_assert_str_eq(sum, "I");
  free(sum);

  sum = add_roman("", "II");
  ck_assert_str_eq(sum, "II");
  free(sum);
}
END_TEST

START_TEST(adding_1s) {
  char* sum = add_roman("I", "I");
  ck_assert_str_eq(sum, "II");
  free(sum);
}
END_TEST

START_TEST(one_plus_two) {
  char* sum = add_roman("I", "II");
  ck_assert_str_eq(sum, "III");
  free(sum);
}
END_TEST

Suite * roman_calculator_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("Roman Calculator");

  /* Core test case */
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, empty_strings_count_as_zero);
  tcase_add_test(tc_core, adding_1s);
  tcase_add_test(tc_core, one_plus_two);
  suite_add_tcase(s, tc_core);

  return s;
}

int failing_tests() {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = roman_calculator_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return number_failed;
}

int main(void) {
  return (failing_tests() == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
