#pragma once
#include <memory>

#include <Expect.h>
#include <TestCase.h>
#include <iostream>

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
      expect(testCaseUser_->wasRun_).toEqual(false);
      testCaseUser_->run();
      expect(testCaseUser_->wasRun_).toEqual(true);
    });

    it("runs_beforeEach", [&]() {
      expect(testCaseUser_->beforeEachWasRun_).toEqual(false);
      testCaseUser_->run();
      expect(testCaseUser_->beforeEachWasRun_).toEqual(true);
    });

    it("runs_second_test", [&]() {
      expect(testCaseUser_->wasRun_).toEqual(false);
      expect(testCaseUser_->secondTestWasRun_).toEqual(false);
      testCaseUser_->run();
      expect(testCaseUser_->wasRun_).toEqual(true);
      expect(testCaseUser_->secondTestWasRun_).toEqual(true);
    });

    it("runs_afterEach", [&]() {
      expect(testCaseUser_->afterEachWasRun_).toEqual(false);
      testCaseUser_->run();
      expect(testCaseUser_->afterEachWasRun_).toEqual(true);
    });
  }
};
} // namespace entw