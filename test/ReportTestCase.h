#pragma once

#include "Report.h"
#include "TestCase.h"

class FailResultMock : public entw::IResult {
  bool wasSuccessful() const override { return false; }
  std::string asString() const override { return "string report"; }
};

class SuccessResultMock : public entw::IResult {
  bool wasSuccessful() const override { return true; }
  std::string asString() const override { return "string report"; }
};

namespace entw {
class ReportTestCase : public TestCase {
public:
  void include() override {
    test("reports the failures as full string", [&](Expect &expect) {
      auto report = Report();
      report.add(std::make_unique<FailResultMock>());

      expect(report.full()).toEqual("string report");
    });

    test("reports the number of failures", [&](Expect &expect) {
      auto report = Report();
      report.add(std::make_unique<FailResultMock>());
      report.add(std::make_unique<FailResultMock>());
      report.add(std::make_unique<SuccessResultMock>());

      expect(report.countFailures()).toEqual(2);
    });
  }
};
} // namespace entw
