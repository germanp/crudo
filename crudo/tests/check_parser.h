#include "cu/cu.h"

// Declarations of tests
TEST(check_strip_spaces);

// Collect tests into test suite
TEST_SUITE(suite) {
    TEST_ADD(check_strip_spaces),
    TEST_SUITE_CLOSURE
};
