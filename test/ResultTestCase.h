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
      assert(result.asString() == "test failed");
      return true;
    });

    it("reports the success results", [&]() {
      Result result(true, "test");
      assert(result.wasSuccessful());
      assert(result.asString() == "test passed");
      return true;
    });
  }
};
} // namespace entw
