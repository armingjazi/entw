#pragma once
#include <TestCase.h>
#include <Expect.h>

namespace entw {
class ExpectTestCase : public TestCase {
 public:

  void include() override {
    it("expect_success_for_equal_number", [&]() {
      Expect<int> expect{};
      assert (expect(50).toEqual(50));
      return true;
    });

    it("expect_failure_for_non_equal_numbers", [&]() {
      Expect<int> expect{};
      assert (!expect(50).toEqual(51));
      return true;
    });

    it("expect_success_for_equal_string", [&]() {
      Expect<std::string> expect;
      assert (expect("test").toEqual("test"));
      return true;
    });

    it("expect_failure_for_non_equal_string", [&]() {
      Expect<std::string> expect;
      assert (expect("test").toEqual("test"));
      return true;
    });
  }
};
} // namespace entw
