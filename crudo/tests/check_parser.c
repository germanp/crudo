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
    assertFalse( strcmp(r->name,"gcc++") );
    assertFalse( strcmp(r->comparator,">=") );
    assertEquals( r->version, 3020100);
    r=r->next;
    assertFalse( strcmp(r->name,"libncurses") );
    assertFalse( strcmp(r->comparator,">=") );
    assertEquals( r->version, 2090500 );
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
  FILE* fp = fopen("test1.control", "r");
  char* buffer = strip_spaces(fp);
  assertEquals(strlen(buffer), 1228);
  //                             ^
  //                             |
  //         `cat test.control | tr -s "\t\n " | wc -c`
  free(buffer);
}

TEST(check_parse_control_1) {
  FILE *fp=fopen("test1.control","r");
  Package* p=parse(fp,0);
  if ( p ) {
    assertFalse( strcmp(p->name,"xserver-xorg-input-vmmouse") );
    assertFalse( strcmp(p->section,"x11") );
    assertEquals( p->size, 176 );
    assertFalse( p->web );
    assertFalse( strcmp(p->maintainer,"Ubuntu X-SWAT <ubuntu-x@lists.ubuntu.com>") );
    assertTrue( p->version == 12060502 );
    assertFalse( strcmp(p->checksum, "a3663a5181215703c0d47d7534c720c5") );
    assertFalse( p->command );
    // Depends //
    if ( p->depends ) {
      assertFalse( strcmp(p->depends->name,"libc6") );
      assertFalse( strcmp(p->depends->comparator,">=") );
      assertEquals( p->depends->version, 2070000 );
      assertFalse( strcmp(p->depends->next->name,"xserver-xorg-core") );
      assertFalse( strcmp(p->depends->next->comparator,">=") );
      assertEquals( p->depends->next->version, 1069900 );
      assertFalse( p->depends->next->next );
    } else {
      assertTrueM(0,"Failed on parsing depends.");
    }
    // Conflicts //
    assertFalse(p->conflicts);
    assertFalse(p->optionals);
    free_package(&p);
    assertFalseM( p , "Failed on package free." );
  } else {
    assertTrueM(1,"Parsing 'test1.control' failed and should not do it.");
  }
}

TEST(check_parse_control_2) {
  crudo_err err;
  Relation* r;
  FILE *fp=fopen("test2.control","r");
  Package* p=parse(fp,&err);
  if ( p ) {
    assertFalse( strcmp(p->name,"python-tk") );
    assertFalse( strcmp(p->section,"python") );
    assertEquals( p->version, 2060500 );
    // Depends //
    r=p->depends;
    if ( r ){
      assertFalse( strcmp(r->name, "python") );
      assertFalse( strcmp(r->comparator, "<<") );
      assertEquals( r->version, 2070000 );
      r=r->next;
      if ( r ) {
      	assertFalse(strcmp(r->name, "python"));
      	assertFalse(strcmp(r->comparator, ">="));
      	assertEquals(r->version,2060000);
      	r=r->next;
      	if ( r ) {
      	  assertFalse(strcmp(r->name,"tk8.5"));
      	  assertFalse(strcmp(r->comparator,">="));
      	  assertEquals(r->version,8050000);
      	} else {
      	  assertFalseM(1,"Expected more dependencies.");
      	    }
      } else {
      	assertFalseM(1,"Expected more dependencies.");
      }
    }
    // End Depends //

    // Conflicts //
    r=p->conflicts;
    if ( r ){
      assertFalse( strcmp(r->name, "python2.3-tk") );
      assertFalse( strcmp(r->comparator, "") );
      assertEquals( r->version, 0 );
      r=r->next;
      if ( r ) {
      	assertFalse(strcmp(r->name, "python2.4-tk"));
      	assertFalse(strcmp(r->comparator, ""));
      	assertEquals(r->version,0);
      } else {
      	assertFalseM(1,"Expected more conflicts.");
      }
    } else {
      assertFalseM(1,"Expected more conflicts.");
    }
    // End Conflicts //
    
    // Optionals //
    r=p->optionals;
    if ( r ){
      assertFalse( strcmp(r->name, "tix") );
      assertFalse( strcmp(r->comparator, "") );
      assertEquals( r->version, 0 );
      r=r->next;
      if ( r ) {
      	assertFalse(strcmp(r->name, "python-tk-dbg"));
      	assertFalse(strcmp(r->comparator, ""));
      	assertEquals(r->version,0);
      } else {
      	assertFalseM(1,"Expected more conflicts.");
      }
    } else {
      assertFalseM(1,"Expected more conflicts.");
    }
    // End Optionals //
  } else {
    char buf[400];
    sprintf(buf,"Parsing 'test2.control' failed and should not do it. When parsing '%s' on field '%s'.\n",err.str_err,err.field);
    assertFalseM(1,buf);
  }
}
