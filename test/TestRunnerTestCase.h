#pragma once
#include <cassert>
#include <ostream>
#include <sstream>

#include "EqualityExpectation.h"
#include "TestCase.h"
#include "TestRunner.h"

namespace entw {

class SuccessTestCase : public TestCase {
public:
  SuccessTestCase() { setName("Success Test Case"); }

  void include() override {
    test(
        "cat follows mice", [&](Expect &expect) {}, 0);
  }
};

class FailureTestCase : public TestCase {
public:
  void include() override {
    test(
        "javascript a wonderful language",
        [&](Expect &expect) {
          throw std::logic_error(
              "failed because js is not a wonderful language");
        },
        0);
  }
};

class MixTestCase : public TestCase {
public:
  void include() override {
    test(
        "cat follows mice", [&](Expect &expect) {}, 0);
    test(
        "dogs follow cats", [&](Expect &expect) {}, 0);
    test(
        "c++ is not used anymore",
        [&](Expect &expect) {
          throw std::logic_error("failed because it is used");
        },
        0);
    test(
        "javascript a wonderful language",
        [&](Expect &expect) {
          throw std::logic_error("failed because it is not");;
        },
        0);
  }
};

class TestRunnerTestCase : public TestCase {
public:
  void include() override {
    test("reports the succeeded tests", [&](Expect &expect) {
      TestRunner testRunner{};

      testRunner.add(std::make_unique<SuccessTestCase>());

      std::stringbuf results;
      std::ostream resultsStream(&results);

      testRunner.run(resultsStream);

      const auto actual = results.str();
      const auto expected = std::string(
          "[\033[32mpassed\033[0m] Success Test Case: cat follows mice\n");

      expect(actual).toEqual(expected);
    });

    test("reports the failed tests", [&](Expect &expect) {
      TestRunner testRunner{};

      testRunner.add(std::make_unique<FailureTestCase>());

      std::stringbuf results;
      std::ostream resultsStream(&results);

      testRunner.run(resultsStream);

      const auto actual = results.str();
      const auto expected = std::string(
          "[\033[31mfailed\033[0m] javascript a wonderful language\n"
          "failed because js is not a wonderful language\n");

      expect(actual).toEqual(expected);
    });

    test("reports the multiple tests", [&](Expect &expect) {
      TestRunner testRunner{};

      testRunner.add(std::make_unique<MixTestCase>());

      std::stringbuf results;
      std::ostream resultsStream(&results);

      testRunner.run(resultsStream);

      const auto actual = results.str();
      const auto expected = std::string(
          "[\033[32mpassed\033[0m] cat follows mice\n"
          "[\033[32mpassed\033[0m] dogs follow cats\n"
          "[\033[31mfailed\033[0m] c++ is not used anymore\n"
          "failed because it is used\n"
          "[\033[31mfailed\033[0m] javascript a wonderful language\n"
          "failed because it is not\n");

      expect(actual).toEqual(expected);
    });

    test("reports the multiple testcases", [&](Expect &expect) {
      TestRunner testRunner{};

      testRunner.add(std::make_unique<SuccessTestCase>());
      testRunner.add(std::make_unique<FailureTestCase>());

      std::stringbuf results;
      std::ostream resultsStream(&results);

      testRunner.run(resultsStream);

      const auto actual = results.str();
      const auto expected = std::string(
          "[\033[32mpassed\033[0m] Success Test Case: cat follows mice\n"
          "[\033[31mfailed\033[0m] javascript a wonderful language\n"
          "failed because js is not a wonderful language\n");

      expect(actual).toEqual(expected);
    });
  }
};
} // namespace entw
