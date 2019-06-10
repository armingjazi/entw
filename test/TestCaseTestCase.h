#pragma once
#include <TestCase.h>
#include <assert.h>

namespace entw {
class TestCaseUser : public TestCase {
 public:
  void describe() override {
    it(test_method);
  }

  bool wasRun_ = false;

  test test_method = [&] () {
    wasRun_ = true;
  };
};

class TestCaseTestCase : public TestCase {
 private:
  TestCaseUser testCaseUser_;


 public:
  void describe() override {
    it(was_run);
  }

  test was_run = [&] () {
    assert(!testCaseUser_.wasRun_);
    testCaseUser_.describe();
    testCaseUser_.run();
    assert(testCaseUser_.wasRun_);
  };
};
}