//test harness include
#include "unity/unity_fixture.h"
//#includes for module under test
#include "sqlite3.h"
#include "package.h"
#include "database.h"
#include "argz.h"
#include <string.h>

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

// Common group code

Relation* r1;
Relation* r2;

TEST_SETUP(database) {
  open_database(DB_FILE);
  r1=init_relation();
  r1->name=strdup("Binutils");
  strcpy(r1->comparator,">=");
  r1->version=4000200;
  r2=init_relation();
  r2->name=strdup("Glibc");
  strcpy(r2->comparator,">=");
  r2->version=2000200;
  r1->next=r2;

}

TEST_TEAR_DOWN(database) {
  close_database();
}

//

TEST(database, add_relations){

  TEST_ASSERT_EQUAL(SQLITE_DONE,add_relations(1,'d',r1));
}

TEST(database, add_package){
  TEST_ASSERT_EQUAL(SQLITE_OK,add_package(&package));
}

TEST(database, run_queryf){
  sqlite3_stmt* pstmt;
  TEST_ASSERT_EQUAL(SQLITE_ROW, run_queryf(&pstmt,"SELECT * FROM package WHERE name = %Q;","gcc"));
  TEST_ASSERT_TRUE(pstmt);
  TEST_ASSERT_EQUAL_STRING("Gcc", sqlite3_column_text(pstmt,1));
  TEST_ASSERT_EQUAL(SQLITE_OK, sqlite3_finalize(pstmt));
}

TEST(database, run_query){
  sqlite3_stmt* pstmt;
  TEST_ASSERT_EQUAL(SQLITE_ROW, run_query(&pstmt,"SELECT * FROM package;"));
  TEST_ASSERT_TRUE(pstmt);
  TEST_ASSERT_EQUAL_STRING("Gcc", sqlite3_column_text(pstmt,1));
  TEST_ASSERT_EQUAL(SQLITE_OK, sqlite3_finalize(pstmt));
}

TEST(database, execute_sql){
  TEST_ASSERT_TRUE(execute_sql("SELECT * FROM Package;"));
  TEST_ASSERT_TRUE(execute_sql("DELETE FROM Package WHERE name = 'Inexistent';"));
  TEST_ASSERT_FALSE(execute_sql("WRONG SQL QUERY;"));
}

TEST(database, find_package){
  Package* p=find_package("gcc");
  TEST_ASSERT_TRUE(p);
  TEST_ASSERT_EQUAL_STRING(package.name, p->name);
  TEST_ASSERT_EQUAL_STRING(package.description, p->description);
  TEST_ASSERT_EQUAL_STRING(package.section, p->section);
  TEST_ASSERT_EQUAL(package.size, p->size);
  TEST_ASSERT_EQUAL(package.version, p->version);
  TEST_ASSERT_EQUAL_STRING(package.web, p->web);
  TEST_ASSERT_EQUAL_STRING(package.maintainer, p->maintainer);
  TEST_ASSERT_EQUAL_STRING(package.checksum, p->checksum);
  free(p);
  p=find_package("unwanted_package");
  TEST_ASSERT_FALSE(p);
}

TEST(database, delete_package){
  TEST_ASSERT_TRUE(delete_package("gcc"));
  TEST_ASSERT_FALSE(delete_package("gcc"));
}

TEST(database, list_packages){
  char* argz=0;
  size_t argz_len=0;
  TEST_ASSERT_EQUAL(SQLITE_ROW,list_packages(&argz,&argz_len,"Gcc"));
  char* entry=0;
  entry=argz_next(argz,argz_len,entry);
  TEST_ASSERT_EQUAL_STRING(package.name, entry);
  entry=argz_next(argz,argz_len,entry);
  TEST_ASSERT_EQUAL_STRING(package.description, entry);
  entry=argz_next(argz,argz_len,entry);
  TEST_ASSERT_EQUAL(package.version, parse_version(entry));

}

//Each group has a TEST_GROUP_RUNNER
TEST_GROUP_RUNNER(database){
  unlink(DB_FILE); // Delete the file if exists
  TEST_ASSERT_EQUAL(SQLITE_OK,init_database(DB_FILE));

  // Test Cases
  RUN_TEST_CASE(database, add_relations);
  RUN_TEST_CASE(database, add_package);
  RUN_TEST_CASE(database, run_query);
  RUN_TEST_CASE(database, execute_sql);
  RUN_TEST_CASE(database, find_package);
  RUN_TEST_CASE(database, list_packages);
  RUN_TEST_CASE(database, delete_package);
}

// -- End Test Group Database -- //
