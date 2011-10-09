#include "cu/cu.h"

// Declarations of tests
TEST(check_parse_relation);
TEST(check_parse_version);
TEST(check_parse_control);
TEST(check_strip_spaces);

// Collect tests into test suite
TEST_SUITE(suite) {
  TEST_ADD(check_strip_spaces),
  TEST_ADD(check_parse_version),
  TEST_ADD(check_parse_relation),
  TEST_ADD(check_parse_control),
  TEST_SUITE_CLOSURE
};
