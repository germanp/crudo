#include "parser.h"
#include "package.h"
#include "cu/cu.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

TEST(check_package_struct) {
  /* Package* p = { */
  /*   "xserver-xorg-input-vmmouse", */
  /*   "X.Org X server -- VMMouse input driver to use with VMWare \nThis package provides the driver for the X11 vmmouse input device.", */
  /*   12060501, */
  /*   "x11", */
  /*   NULL, */
  /*   NULL, */
  /*   NULL */
  /* } */
  char* m="milanesa";
  Package p = {
    m,
    m,
    12060501,
    m,
    NULL,
    NULL,
    NULL
  };
  printf("Name: %s\n",p.name);
  printf("Description: %s\n",p.description);
  printf ("Version: %lu\n",p.version);
  printf ("Section: %s\n",p.section);
}

TEST(check_strip_spaces) {
  FILE* fp = fopen("test.control", "r");
  char* buffer = strip_spaces(fp);
  assertEquals(strlen(buffer), 1269);
  //                                       ^
  //                                       |
  //                                       |
  //         `cat test.control | tr -s "\t\n " | wc -
  free(buffer);
}
