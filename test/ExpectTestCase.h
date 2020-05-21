#pragma once
#include <Expect.h>
#include <TestCase.h>
#include <iostream>

namespace entw {
class ExpectTestCase : public TestCase {
public:
  void include() override {
    it("expect_success_for_equal_number", [&]() {
      expect<int>(50).toEqual(50);
    });

    it("expect_failure_for_non_equal_numbers", [&]() {
      try {
        expect<int>(50).toEqual(51);
      }
      catch (const std::exception& e) {
        assert(std::string(e.what()) == std::string("expected\n 51\nreceived\n 50"));
      }
    });

    it("expect_success_for_equal_string", [&]() {
      expect<std::string>("test").toEqual("test");
    });

    it("expect_failure_for_non_equal_string", [&]() {
      try {
        expect<std::string>("badString").toEqual("goodString");
      }
      catch (const std::exception& e) {
        assert(std::string(e.what()) == "expected\n goodString\nreceived\n badString");
      }
    });
  }
};
} // namespace entw
