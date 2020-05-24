#include "ExpectTestCase.h"
#include "ReportTestCase.h"
#include "ResultTestCase.h"
#include "SubstituteTestCase.h"
#include "TestCaseTestCase.h"
#include "TestRunner.h"
#include "TestRunnerTestCase.h"
#include "TestTestCase.h"

int main(int argc, char **argv) {
  entw::TestRunner testRunner{};
  testRunner.add(std::make_unique<entw::TestCaseTestCase>());
  testRunner.add(std::make_unique<entw::ExpectTestCase>());
  testRunner.add(std::make_unique<entw::TestTestCase>());
  testRunner.add(std::make_unique<entw::ResultTestCase>());
  testRunner.add(std::make_unique<entw::TestRunnerTestCase>());
  testRunner.add(std::make_unique<entw::ReportTestCase>());
  testRunner.add(std::make_unique<entw::SubstituteTestCase>());

  return testRunner.run(std::cout);
}