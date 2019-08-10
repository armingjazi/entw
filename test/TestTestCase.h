#pragma once
#include <TestCase.h>
#include <Test.h>

namespace entw {
class TestTestCase : public TestCase {
 public:

  void include() override {
    it("returns_true_for_passing_test", []() {
      Test test_("test name", []() {
        return true;
      });
      assert (test_()->wasSuccessful());
      return true;
    });
    it("returns_false_for_failing_test", []() {
      Test test_("test name", []() {
        return false;
      });
      assert (!test_()->wasSuccessful());
      return true;
    });
  }
};
} // namespace entw
