#pragma once
#include <cassert>
#include <memory>

#include <TestCase.h>

namespace entw {
class SucceedingTestCase : public TestCase {
public:
  void runBeforeEach() override { beforeEachWasRun_ = true; }

  void runAfterEach() override { afterEachWasRun_ = true; }

  void include() override {
    it("was_run", [&]() {
      wasRun_ = true;
      return true;
    });
    it("was_second_run", [&]() {
      secondTestWasRun_ = true;
      return true;
    });
  }

  bool wasRun_ = false;
  bool secondTestWasRun_ = false;
  bool beforeEachWasRun_ = false;
  bool afterEachWasRun_ = false;
};

class TestCaseTestCase : public TestCase {
private:
  std::unique_ptr<SucceedingTestCase> testCaseUser_;

public:
  void runBeforeEach() override {
    testCaseUser_ = std::make_unique<SucceedingTestCase>();
  }

  void runAfterEach() override { testCaseUser_ = nullptr; }

  void include() override {
    it("runs_test", [&]() {
      assert(!testCaseUser_->wasRun_);
      testCaseUser_->run();
      assert(testCaseUser_->wasRun_);
      return true;
    });

    it("runs_beforeEach", [&]() {
      assert(!testCaseUser_->beforeEachWasRun_);
      testCaseUser_->run();
      assert(testCaseUser_->beforeEachWasRun_);
      return true;
    });

    it("runs_second_test", [&]() {
      assert(!testCaseUser_->wasRun_);
      assert(!testCaseUser_->secondTestWasRun_);
      testCaseUser_->run();
      assert(testCaseUser_->wasRun_);
      assert(testCaseUser_->secondTestWasRun_);
      return true;
    });

    it("runs_afterEach", [&]() {
      assert(!testCaseUser_->afterEachWasRun_);
      testCaseUser_->run();
      assert(testCaseUser_->afterEachWasRun_);
      return true;
    });
  }
};
}