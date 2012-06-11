#include "cu/cu.h"

// Declarations of tests
TEST(check_init_database);
TEST(check_add_package);
TEST(check_add_relations);
//TEST(check_get_package);

// Collect tests into test suite
TEST_SUITE(database) {
  TEST_ADD(check_init_database),
  TEST_ADD(check_add_package),
    //  TEST_ADD(check_add_relations),
    //  TEST_ADD(check_get_package),
  TEST_SUITE_CLOSURE
};
