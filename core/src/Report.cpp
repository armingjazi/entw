#include <string>
#include <Report.h>

namespace entw {
Report::Report(std::vector<std::string> results)
: results_(std::move(results)) { }

std::string Report::failures() {
  if (results_.empty())
    return "None";
  std::string report;
  for (const auto r : results_) {
    if (report != "")
      report += "\n";
    report += r;
  }
  return report;
}

} // namespace entw