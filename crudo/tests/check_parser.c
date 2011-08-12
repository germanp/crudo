#include "parser.h"
#include "cu/cu.h"
#include <stdio.h>
#include <string.h>

TEST(check_strip_spaces) {
  FILE* fp = fopen("test.control", "r");
  char* buffer;
  assertEquals(strlen(buffer), 1269);
  //                                       ^
  //                                       |
  //                                       |
  //         `cat test.control | tr -s "\t\n " | wc -
  free(buffer);
}
