#include <typeinfo>
#include <iostream>
#include "TestCaseTestCase.h"

int main(int argc, char **argv) {
  auto wasRunTestCase = entw::WasRunTestCase();
  wasRunTestCase.run();
  auto wasSetupTestCase = entw::WasSetupTestCase();
  wasSetupTestCase.run();
}