#include <typeinfo>
#include <iostream>
#include "TestCaseTestCase.h"

int main(int argc, char **argv) {
  entw::TestCaseTestCase testCase_;
  testCase_.describe();
  testCase_.run();
}