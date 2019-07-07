#include <TestCase.h>

namespace entw {
void TestCase::run() {
  include();
  for (auto&& testMethod : testMethods_) {
    runBeforeEach();
    testMethod();
    runAfterEach();
  }
}
void TestCase::it(TestCase::test &method) {
  testMethods_.push_back(method);
}
} // namespace entw