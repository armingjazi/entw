#include "TestCaseTestCase.h"
#include "ExpectTestCase.h"
#include "TestTestCase.h"
#include "ResultTestCase.h"

int main(int argc, char **argv) {
  entw::TestCaseTestCase test_case_test_case;
  entw::ExpectTestCase expect_test_case;
  entw::TestTestCase test_test_case;
  entw::ResultTestCase result_test_case;
  test_test_case.run();
  test_case_test_case.run();
  expect_test_case.run();
  result_test_case.run();
}