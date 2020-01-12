#pragma once
#include <cassert>
#include <sstream>
#include <ostream>

#include <TestCase.h>
#include <Expect.h>
#include <TestRunner.h>

namespace entw {

class SuccessTestCase : public TestCase {
public:
  void include() override {
    it("cat follows mice", [&]() { return true; });
  }
};

class FailureTestCase : public TestCase {
public:
  void include() override {
    it("javascript a wonderful language", [&]() { return false; });
  }
};

class MixTestCase : public TestCase {
public:
  void include() override {
    it("cat follows mice", [&]() { return true; });
    it("dogs follow cats", [&]() { return true; });
    it("c++ is not used anymore", [&]() { return false; });
    it("javascript a wonderful language", [&]() { return false; });
  }
};

class TestRunnerTestCase : public TestCase {
public:
  void include() override {
    it("reports the succeeded tests", [&]() {
      TestRunner testRunner {};

      testRunner.add(std::make_unique<SuccessTestCase>());

      std::stringbuf results;
      std::ostream resultsStream(&results);

      testRunner.run(resultsStream);

      const auto actual = results.str();
      const auto expected =
          std::string("[\033[32mpassed\033[0m] cat follows mice");

      assert(actual == expected);

      return true;
    });

    it("reports the failed tests", [&]() {
      TestRunner testRunner {};

      testRunner.add(std::make_unique<FailureTestCase>());

      std::stringbuf results;
      std::ostream resultsStream(&results);

      testRunner.run(resultsStream);

      const auto actual = results.str();
      const auto expected =
          std::string("[\033[31mfailed\033[0m] javascript a wonderful language");

      assert(actual == expected);

      return true;
    });

    it("reports the multiple tests", [&]() {
      TestRunner testRunner {};

      testRunner.add(std::make_unique<MixTestCase>());

      std::stringbuf results;
      std::ostream resultsStream(&results);

      testRunner.run(resultsStream);

      const auto actual = results.str();
      const auto expected =
          std::string("[\033[32mpassed\033[0m] cat follows mice\n"
                      "[\033[32mpassed\033[0m] dogs follow cats\n"
                      "[\033[31mfailed\033[0m] c++ is not used anymore\n"
                      "[\033[31mfailed\033[0m] javascript a wonderful language");

      assert(actual == expected);

      return true;
    });
  }
};
} // namespace entw
