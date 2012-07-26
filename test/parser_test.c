//test harness include
#include "unity/unity_fixture.h"

//#includes for module under test
#include <string.h>
#include <stdio.h>
#include "parser.h"
#include <errno.h>

#define ignore_result(x) ({ typeof(x) z = x; (void)sizeof z; })


TEST_GROUP(parser);

TEST_SETUP(parser){

}

TEST_TEAR_DOWN(parser){

}

TEST(parser, strip_spaces){
  FILE* fp = fopen("test1.control", "r");
  char* buffer = strip_spaces(fp);
  TEST_ASSERT_EQUAL(1281,strlen(buffer));
  //                 ^
  //                 |
  // `cat test.control | tr -s "\t\n " | wc -c`
  free(buffer);
  fclose(fp);
}

TEST(parser, parse_version){
  TEST_ASSERT_EQUAL_INT32(2340107,parse_version("1:2.34.1-7"));
  TEST_ASSERT_EQUAL_INT32(3021100,parse_version("3.2.11"));
  TEST_ASSERT_EQUAL_INT32(0,parse_version("1:333.4.3-b"));
}

TEST(parser, parse_relations){
  Relation* relations;
  TEST_ASSERT_TRUE(parse_relations(&relations," gcc++ (>= 3.2.1), \n libncurses (>=2.9.5)"));
  TEST_ASSERT_EQUAL_STRING("gcc++", relations->name);
  TEST_ASSERT_EQUAL_STRING(">=", relations->comparator);
  TEST_ASSERT_EQUAL(3020100, relations->version);
  relations=relations->next;
  TEST_ASSERT_EQUAL_STRING("libncurses", relations->name);
  TEST_ASSERT_EQUAL_STRING(">=", relations->comparator);
  TEST_ASSERT_EQUAL(2090500, relations->version);
}

TEST(parser, parse_control){
  FILE* fp=fopen("test1.control","r");
  if ( fp ){ 
    Package* p=parse(fp);
    TEST_ASSERT_TRUE( p );
  }
  fclose(fp);
}

TEST_GROUP_RUNNER(parser)
{
  ignore_result(freopen("parser.err", "w+", stderr));
  RUN_TEST_CASE(parser, strip_spaces);
  RUN_TEST_CASE(parser, parse_version);
  RUN_TEST_CASE(parser, parse_relations);
  RUN_TEST_CASE(parser, parse_control);
}
