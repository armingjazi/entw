#pragma once

#include <functional>
#include <vector>
#include <string>

#include "Test.h"
#include "IReport.h"

namespace entw {
class TestCase {
public:
  TestCase() = default;
  virtual ~TestCase() = default;;

  ReportPtr run();

  void it(const std::string &name, const Test::It &method);

  void setName(const std::string& name);

  virtual void include() = 0;

  virtual void runBeforeEach(){};

  virtual void runAfterEach(){};

private:
  std::vector<Test> tests_;
  std::string name_ = "";
};
using TestCasePtr = std::unique_ptr<TestCase>;

} // namespace entw