#pragma once
#include <Expect.h>
#include <TestCase.h>
#include <iostream>

namespace entw {
class ExpectTestCase : public TestCase {
public:
  void include() override {
    it("expect_success_for_equal_number", [&]() {
      assert(expect<int>(50).toEqual(50));
      return true;
    });

    it("expect_failure_for_non_equal_numbers", [&]() {
      assert(!expect<int>(50).toEqual(51));
      return true;
    });

    it("expect_success_for_equal_string", [&]() {
      assert(expect<std::string>("test").toEqual("test"));
      return true;
    });

    it("expect_failure_for_non_equal_string", [&]() {
      assert(expect<std::string>("test").toEqual("test"));
      return true;
    });
  }
};
} // namespace entw
