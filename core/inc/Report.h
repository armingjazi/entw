#pragma once

#include <string>
#include <vector>

#include "IResult.h"
#include "IReport.h"

namespace entw {
class Report : public IReport {
public:
  std::string failures() override;
  void add(ResultPtr result_ptr) override;

private:
  std::vector<ResultPtr> results_;
};
} // namespace entw