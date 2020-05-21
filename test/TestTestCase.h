#pragma once
#include <Test.h>
#include <TestCase.h>

namespace entw {
class TestTestCase : public TestCase {
public:
  void include() override {
    it("returns_true_for_passing_test", []() {
      Test test_("test name", []() { return true; });
      expect(test_()->wasSuccessful()).toEqual(true);
    });
    it("returns_false_for_failing_test", []() {
      Test test_("test name", []() { throw std::logic_error("failed"); });
      expect(test_()->wasSuccessful()).toEqual(false);
    });
  }
};
} // namespace entw
