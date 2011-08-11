#include "tests.h"
#include "parser.h"
#include <stdio.h>

START_TESTS(){

  START_TEST("check_strip_spaces") {
    FILE* f;
    ASSERT(0 == strip_spaces(f));
  } END_TEST()

} END_TESTS()
