#pragma once
#include "Test.h"
#include "TestCase.h"

namespace entw {
class TestTestCase : public TestCase {
public:
  void include() override {
    test("returns true for passing test", [](Expect &expect) {
      Test test(
          "test name", [](Expect &expect) {}, 0);
      expect(test()->wasSuccessful()).toEqual(true);
    });

    test("returns true for passing test", [](Expect &expect) {
      Test test(
          "test name", [](const Expect &expect) {}, 0);
      expect(test()->wasSuccessful()).toEqual(true);
    });

    test("returns unsuccessful for incorrect number of assertions",
         [](Expect &expect) {
           Test test(
               "test name", [](const Expect &expect) {}, 1);

           expect(test()->wasSuccessful()).toEqual(false);
           expect(test()->asString())
               .toEqual(
                   "[\033[31mfailed\033[0m] test name\nexpected 1 assertions\n"
                   "received 0");
         }, 2);
  }
};
} // namespace entw
