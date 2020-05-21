#include <string>

#include <Report.h>

namespace entw {
std::string Report::failures() {
  std::string report;
  for (const auto &r : results_) {
    if (!report.empty())
      report += "\n";
    if (!r->wasSuccessful())
      report += r->asString();
  }
  if (report.empty())
    return "None";
  return report;
}
void Report::add(ResultPtr result_ptr) {
  results_.emplace_back(std::move(result_ptr));
}
std::string Report::full() {
  std::string report;
  for (const auto &r : results_) {
    if (!report.empty())
      report += "\n";
    report += r->asString();
  }
  if (report.empty())
    return "No Tests";
  return report;
}
std::size_t Report::countFailures() {
  std::size_t count = 0;
  for (const auto &r : results_) {
    if (!r->wasSuccessful())
      ++count;
  }
  return count;
}
} // namespace entw