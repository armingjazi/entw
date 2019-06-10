#include "WasRun.h"

namespace entw {
WasRun::WasRun() : TestCase() {
}
bool WasRun::wasRun() {
  return wasRun_;
}
void WasRun::testMethod() {
  wasRun_ = true;
}
void WasRun::run() {
  TestCase::run();
  testMethod();
}
void WasRun::setUp() {
  wasSetup_ = true;
  wasRun_ = false;
}
bool WasRun::wasSetup() {
  return wasSetup_;
}
}
