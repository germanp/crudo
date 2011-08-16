#include "parser.h"
#include "package.h"
#include "cu/cu.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

TEST(check_package_struct) {
  //Relation dep = { .name="libc", .comparator=">=", .version=02070000};
  /* Package p = { */
  /*   .name = "xserver-xorg-input-vmmouse", */
  /*   .description = "X.Org X server -- VMMouse input driver to use with VMWare \nThis package provides the driver for the X11 vmmouse input device.", */
  /*   .version = 12060501, */
  /*   .section = "x11", */
  /*   //    .depends = dep, */
  /* }; */
  Package* p = parse("test.control");
  /* assertFalse( strcmp(p->name,"xserver-xorg-input-vmmouse") ); */
}

TEST(check_strip_spaces) {
  FILE* fp = fopen("test.control", "r");
  char* buffer = strip_spaces(fp);
  assertEquals(strlen(buffer), 1268);
  //                                       ^
  //                                       |
  //                                       |
  //         `cat test.control | tr -s "\t\n " | wc -b`
  free(buffer);
}
