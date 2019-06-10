#pragma once

#include "TestCase.h"

namespace entw {
class WasRun : public TestCase {
 public:
  explicit WasRun();

  bool wasRun();

  void setUp() override;

  void testMethod();

  bool wasSetup();

  void run() override;

 private:
  bool wasRun_ = false;
  bool wasSetup_ = false;
};
}

