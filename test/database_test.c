//test harness include
#include "unity/unity_fixture.h"
//#includes for module under test
#include "sqlite3.h"
#include "package.h"

#define DB_FILE "test.cdb"

// -- Begin Test Group Database -- //
TEST_GROUP(database); 

static Package package={
  .name = "Gcc",
  .description = "GNU Compiler Collection (Conjunto de compiladores creados por el proyecto GNU). Es el compilador estandar para la mayoria de los sistemas operativos similares a Unix. Gcc soporta una gran cantidad de arquitecturas y puede compilar programas en C, C++, Fortran, Ada, Java, Objetive C, Pascal, entre otros.",
  .section = "compilers",
  .size = 102200121,
  .web = "http://gcc.gnu.org/",
  .maintainer = "core",
  .version = 4000200,
  .checksum = "1b0787539705920b5389766dd37114c1",
};

Relation relation={
  .name = "Binutils",
  .comparator = ">=",
  .version = 2210100,
  .next = 0
};

// Common group code

TEST_SETUP(database) {
  open_database(DB_FILE);
}

TEST_TEAR_DOWN(database) {
  close_database();
}

//

TEST(database, add_relation){
  Relation* prelation=&relation;
  TEST_ASSERT_EQUAL(SQLITE_DONE,add_relations(package.name,'d',&prelation));
}

TEST(database, add_package){
  TEST_ASSERT_EQUAL(SQLITE_OK,add_package(&package));
}


//Each group has a TEST_GROUP_RUNNER
TEST_GROUP_RUNNER(database){
  unlink(DB_FILE); // Delete the file if exists
  TEST_ASSERT_EQUAL(SQLITE_OK,init_database(DB_FILE));

  // Test Cases
  RUN_TEST_CASE(database, add_relation);
  RUN_TEST_CASE(database, add_package);
}

// -- End Test Group Database -- //
