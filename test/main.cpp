#include "TestCaseTestCase.h"
#include "ExpectTestCase.h"
#include "TestTestCase.h"
#include "ResultTestCase.h"
#include "TestRunnerTestCase.h"
#include "TestRunner.h"

int main(int argc, char **argv) {
  entw::TestRunner testRunner{};
  testRunner.add(std::make_unique<entw::TestCaseTestCase>());
  testRunner.add(std::make_unique<entw::ExpectTestCase>());
  testRunner.add(std::make_unique<entw::TestTestCase>());
  testRunner.add(std::make_unique<entw::ResultTestCase>());
  testRunner.add(std::make_unique<entw::TestRunnerTestCase>());

  testRunner.run(std::cout);
}