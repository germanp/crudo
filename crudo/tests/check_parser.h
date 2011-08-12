#include "cu/cu.h"

// Declarations of tests
TEST(test1);

// Collect tests into test suite
TEST_SUITE(T1) {
    TEST_ADD(test1),
    TEST_SUITE_CLOSURE
};
