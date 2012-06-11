#include "database.h"
#include "cu/cu.h"
#include <unistd.h>
#include <stdio.h>
#include <assert.h>

const char* DB_FILE="test.cdb";

Package p={
  .name = "Gcc",
  .description = "GNU Compiler Collection (Conjunto de compiladores creados por el proyecto GNU). Es el compilador estandar para la mayoria de los sistemas operativos similares a Unix. Gcc soporta una gran cantidad de arquitecturas y puede compilar programas en C, C++, Fortran, Ada, Java, Objetive C, Pascal, entre otros.",
  .section = "compilers",
  .size = 102200121,
  .web = "http://gcc.gnu.org/",
  .maintainer = "core",
  .version = 4000200,
  .checksum = "1b0787539705920b5389766dd37114c1",
};

TEST(check_init_database){
  unlink(DB_FILE); // Delete the file if exists
  assertEquals(init_database(DB_FILE),SQLITE_OK);
}

TEST(check_add_package){
  if ( open_database(DB_FILE) ){
    assert(add_package(&p)==SQLITE_OK);
    assertFalseM(add_package(&p)==SQLITE_OK,"Duplicated package should fail.");
  } else {
    assertTrueM(0,"Could not open the database.");
  }
  close_database();
}

TEST(check_add_relations){
  Relation r1={
    .name = "Binutils",
    .comparator = ">=",
    .version = 2210100,
    .next = 0
  };
  Relation *r=&r1;
  if ( open_database(DB_FILE) ){
    assertEqualsM(add_relations(p.name,'d',&r),SQLITE_DONE,"Failed adding a relation.");
    assertNotEqualsM(add_relations(p.name,'d',&r),SQLITE_DONE,"Adding the same relation must be fail.");
  } else {
    assertTrueM(0,"Could not open the database.");
  }
  close_database();
}

TEST(check_find_id_package){
  if ( open_database(DB_FILE) ){
    
  } else {
    assertTrueM(0,"Could not open the database.");
  }
  close_database();
}
