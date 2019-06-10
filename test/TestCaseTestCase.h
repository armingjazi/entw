#pragma once
#include <iostream>
#include <TestCase.h>

namespace entw {
class TestCaseUser : public TestCase {
 public:
  void include() override {
    test(test_method);
  }

  bool wasRun_ = false;

  TestMethodType test_method = [&] () {
    wasRun_ = true;
  };
};

class TestCaseTestCase : public TestCase {
 private:
  TestCaseUser testCaseUser_;


 public:
  void include() override {
    test(was_run);
  }

  TestMethodType was_run = [&] () {
    assert(!testCaseUser_.wasRun_);
    testCaseUser_.include();
    testCaseUser_.run();
    assert(testCaseUser_.wasRun_);
  };
};
}