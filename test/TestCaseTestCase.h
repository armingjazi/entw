#pragma once
#include <iostream>
#include <TestCase.h>
#include <WasRun.h>

namespace entw {
class WasRunTestCase : public TestCase {
 private:
  WasRun test_;

 public:
  void setUp() override {
    test_ = WasRun();
  }

  void run() override {
    assert(!test_.wasRun());
    test_.run();
    assert(test_.wasRun());
  }
};

class WasSetupTestCase : public TestCase {
 private:
  WasRun test_;

 public:
  void setUp() override {
    test_ = WasRun();
  }

  void run() override {
    assert(!test_.wasSetup());
    test_.run();
    assert(test_.wasSetup());
  }
};
}