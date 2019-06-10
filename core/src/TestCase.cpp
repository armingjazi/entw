#include <TestCase.h>

namespace entw {
void TestCase::run() {
  testMethod_();
}
void TestCase::test(TestCase::TestMethodType &method) {
  testMethod_ = method;
}
} // namespace entw