//#include "parser.h"
#include "cu/cu.h"
//#include <stdio.h>
//#include <string.h>

TEST(test1) {
    assertTrue(1);
    printf("Hello from test1\n");
    assertEquals(1, 1);
}

/* START_TESTS(){ */

/*   START_TEST("check_strip_spaces") { */
/*     FILE* fp = fopen("test.control", "r");                               */
/*     ASSERT_EQUALS(strlen(strip_spaces(fp)), 1268); */
/* 		  //                         ^ */
/* 		  //                         | */
/* 		  //                         | */
/* 		  // `cat test.control | tr -s "\n " | wc -c` */
/*   } END_TEST() */
/* } END_TESTS() */
