#include <TestCase.h>

namespace entw {
void TestCase::run() {
  testMethod_();
}
void TestCase::it(TestCase::test &method) {
  testMethod_ = method;
}
} // namespace entw