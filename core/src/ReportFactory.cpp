#include <vector>
#include <Report.h>

#include "ReportFactory.h"

namespace entw {
ReportPtr ReportFactory::makeReport(const std::vector<std::string> &results) {
  return std::make_unique<Report>(results);
}
} // namespace entw
