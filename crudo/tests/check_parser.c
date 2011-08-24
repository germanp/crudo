#include "parser.h"
#include "package.h"
#include "cu/cu.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

TEST(check_parse_relation){
  Relation rel={
    // SEGUIR ACÁ
  }
  assertTrue(1);
}


TEST(check_parse_version){
  assertEquals(parse_version("1:2.34.1-7"),2340107);
  assertEquals(parse_version("1:333.4.3-b"),0);
}

TEST(check_strip_spaces) {
  FILE* fp = fopen("test.control", "r");
  char* buffer = strip_spaces(fp);
  assertEquals(strlen(buffer), 1261);
  //                             ^
  //                             |
  //                             |
  //         `cat test.control | tr -s "\t\n " | wc -c`
  free(buffer);
}

TEST(check_package_struct) {
  //Relation dep = { .name="libc", .comparator=">=", .version=02070000};
  /* Package p = { */
  /*   .name = "xserver-xorg-input-vmmouse", */
  /*   .description = "X.Org X server -- VMMouse input driver to use with VMWare \nThis package provides the driver for the X11 vmmouse input device.", */
  /*   .version = 12060501, */
  /*   .section = "x11", */
  /*   .depends = dep, */
  /* }; */
  Package* p = parse("test.control");
  assertFalseM(p,"Parsing control file failed, syntaxis is wrong.");
  if ( p ) {
    assertFalse( strcmp(p->name,"xserver-xorg-input-vmmouse") );
    assertFalse( strcmp(p->section,"x11") );
    assertEquals( p->version, 12060502 );
  }
}
