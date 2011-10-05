#include "parser.h"
#include "error.h"
#include "package.h"
#include "cu/cu.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

TEST(check_parse_relation){
  crudo_err err;
  Relation* r;
  parse_relation(&r," gcc++ (>= 3.2.1), \n libncurses (>=2.9.5)",&err);
  assertTrue(r);
  if ( r ) {
    //printf ("%s\n",r->name);
    //assertFalse( strcmp(r->name,"gcc++") );
    /* assertFalse( strcmp(r->comparator,">=") ); */
    /* assertEquals( r->version, 3020100); */
    /* r=r->next; */
    /* assertFalse( strcmp(r->name,"libncurses") ); */
    /* assertFalse( strcmp(r->comparator,">=") ); */
    /* assertEquals( r->version, 2090500 ); */
  }
}


TEST(check_parse_version){
  assertEquals(parse_version("1:2.34.1-7",0),2340107);
  assertEquals(parse_version("3.2.11",0),3021100);
  crudo_err err;
  parse_version("1:333.4.3-b",&err);
  assertEquals(err.code,CRUDO_PARSE_ERROR);
}

TEST(check_strip_spaces) {
  FILE* fp = fopen("test.control", "r");
  char* buffer = strip_spaces(fp);
  assertEquals(strlen(buffer), 1228);
  //                             ^
  //                             |
  //         `cat test.control | tr -s "\t\n " | wc -c`
  free(buffer);
}

TEST(check_parse_control) {
  Package* p=parse("test.control",0);
  assertTrueM(p,"Parsing control file failed.");

  if ( p ) {
    assertFalse( strcmp(p->name,"xserver-xorg-input-vmmouse") );
    assertFalse( strcmp(p->section,"x11") );
    assertEquals( p->version, 12060502 );
    assertTrueM( p->depends , "Parsing depends fail." );
    // Depends //
    if ( p->depends ) {
      assertFalse( strcmp(p->depends->name,"libc6") );
      assertFalse( strcmp(p->depends->comparator,">=") );
      assertEquals( p->depends->version, 2070000 );
      assertFalse( strcmp(p->depends->next->name,"xserver-xorg-core") );
      assertFalse( strcmp(p->depends->next->comparator,">=") );
      assertEquals( p->depends->next->version, 1069900 );
      assertFalse( p->depends->next->next );
    }
    // //
    
    free_package(&p);
    assertFalseM( p , "Failed on package free." );
   }
}
