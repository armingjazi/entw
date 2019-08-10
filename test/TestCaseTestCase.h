#pragma once
#include <cassert>
#include <memory>

#include <TestCase.h>
#include <iostream>

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

class FailingTestCase : public TestCase {
  void include() override {
    it("was_failed_1", [&]() {
      return false;
    });
    it("was_failed_2", [&]() {
      return false;
    });
  }
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

    it("fails", [&]() {
      FailingTestCase failing_test_case;
      const auto actual = failing_test_case.run()->failures();
      const auto expected = std::string("was_failed_1 failed\nwas_failed_2 failed");
      assert(actual == expected);
      return true;
    });

    it("succeeds", [&]() {
      assert(testCaseUser_->run()->failures() == "None");
      return true;
    });
  }
};
}