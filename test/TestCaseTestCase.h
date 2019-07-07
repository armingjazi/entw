#pragma once
#include <assert.h>
#include <memory>

#include <TestCase.h>

namespace entw {
class TestCaseUser : public TestCase {
 public:
  void runBeforeEach() override {
    beforeEachWasRun_ = true;
  }

  void runAfterEach() override {
    afterEachWasRun_ = true;
  }

  void include() override {
    it(test_method);
    it(test_second_method);
  }

  bool wasRun_ = false;
  bool secondTestWasRun_ = false;
  bool beforeEachWasRun_ = false;
  bool afterEachWasRun_ = false;

  test test_method = [&] () {
    wasRun_ = true;
  };

  test test_second_method = [&] () {
    secondTestWasRun_ = true;
  };
};

class TestCaseTestCase : public TestCase {
 private:
  std::unique_ptr<TestCaseUser> testCaseUser_;


 public:
  void runBeforeEach() override {
    testCaseUser_ = std::make_unique<TestCaseUser>();
  }

  void runAfterEach() override {
    testCaseUser_ = nullptr;
  }

  void include() override {
    it(runs_test);
    it(runs_beforeEach);
    it(runs_second_test);
    it(runs_afterEach);
  }

  test runs_test = [&] () {
    assert(!testCaseUser_->wasRun_);
    testCaseUser_->run();
    assert(testCaseUser_->wasRun_);
  };

  test runs_beforeEach = [&] () {
    assert(!testCaseUser_->beforeEachWasRun_);
    testCaseUser_->run();
    assert(testCaseUser_->beforeEachWasRun_);
  };

  test runs_second_test = [&] () {
    assert(!testCaseUser_->wasRun_);
    assert(!testCaseUser_->secondTestWasRun_);
    testCaseUser_->run();
    assert(testCaseUser_->wasRun_);
    assert(testCaseUser_->secondTestWasRun_);
  };

  test runs_afterEach = [&] () {
    assert(!testCaseUser_->afterEachWasRun_);
    testCaseUser_->run();
    assert(testCaseUser_->afterEachWasRun_);
  };
};
}