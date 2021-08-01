#pragma once
#include <memory>

#include <EqualityExpectation.h>
#include <TestCase.h>
#include <iostream>

namespace entw {
class SucceedingTestCase : public TestCase {
public:
  void runBeforeEach() override { beforeEachWasRun_ = true; }

  void runAfterEach() override { afterEachWasRun_ = true; }

  void include() override {
    it("was_run", [&](Expect &expect) { wasRun_ = true; });
    it("was_second_run",
       [&](Expect &expect) { secondTestWasRun_ = true; });
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
    it("runs_test", [&](Expect &expect) {
      expect(testCaseUser_->wasRun_).toEqual(false);
      testCaseUser_->run();
      expect(testCaseUser_->wasRun_).toEqual(true);
    }, 2);

    it("runs_beforeEach", [&](Expect & expect) {
      expect(testCaseUser_->beforeEachWasRun_).toEqual(false);
      testCaseUser_->run();
      expect(testCaseUser_->beforeEachWasRun_).toEqual(true);
    }, 2);

    it("runs_second_test", [&](Expect & expect) {
      expect(testCaseUser_->wasRun_).toEqual(false);
      expect(testCaseUser_->secondTestWasRun_).toEqual(false);
      testCaseUser_->run();
      expect(testCaseUser_->wasRun_).toEqual(true);
      expect(testCaseUser_->secondTestWasRun_).toEqual(true);
    }, 4);

    it("runs_afterEach", [&](Expect & expect) {
      expect(testCaseUser_->afterEachWasRun_).toEqual(false);
      testCaseUser_->run();
      expect(testCaseUser_->afterEachWasRun_).toEqual(true);
    }, 2);
  }
};
} // namespace entw