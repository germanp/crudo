#include "unity/unity_fixture.h"

static void runAllTests() {
  RUN_TEST_GROUP(database);
  RUN_TEST_GROUP(parser);
  //...
}

int main(int argc, char * argv[]) {
  return UnityMain(argc, argv, runAllTests);
}
