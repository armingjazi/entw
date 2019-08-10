#pragma once

#include <vector>
#include <IReport.h>

namespace entw
{
class ReportFactory {
 public:
  ReportPtr makeReport(const std::vector<std::string>& results);
};
} // namespace entw