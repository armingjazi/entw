#pragma once
#include <TestCase.h>
#include <Result.h>

namespace entw {
class ResultTestCase : public TestCase {
public:
  void include() override {
    it("reports the failed results", [&]() {
      Result result(false, "test");
      assert(!result.wasSuccessful());
      assert(result.asString() == std::string("[\033[31mfailed\033[0m] test"));
      return true;
    });

    it("reports the success results", [&]() {
      Result result(true, "another test");
      assert(result.wasSuccessful());
      assert(result.asString() == std::string("[\033[32mpassed\033[0m] another test"));
      return true;
    });
  }
};
} // namespace entw
