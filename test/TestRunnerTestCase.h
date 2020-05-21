#pragma once
#include <cassert>
#include <ostream>
#include <sstream>

#include <Expect.h>
#include <TestCase.h>
#include <TestRunner.h>

namespace entw {

class SuccessTestCase : public TestCase {
public:
  SuccessTestCase() { setName("Success Test Case"); }

  void include() override {
    it("cat follows mice", [&]() { return true; });
  }
};

class FailureTestCase : public TestCase {
public:
  void include() override {
    it("javascript a wonderful language", [&]() {
      throw std::logic_error("failed because js is not a wonderful language");
    });
  }
};

class MixTestCase : public TestCase {
public:
  void include() override {
    it("cat follows mice", [&]() { return true; });
    it("dogs follow cats", [&]() { return true; });
    it("c++ is not used anymore", [&]() {
      throw std::logic_error("failed because it is used");
      ;
    });
    it("javascript a wonderful language", [&]() {
      throw std::logic_error("failed because it is not");
      ;
    });
  }
};

class TestRunnerTestCase : public TestCase {
public:
  void include() override {
    it("reports the succeeded tests", [&]() {
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

    it("reports the failed tests", [&]() {
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

    it("reports the multiple tests", [&]() {
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

    it("reports the multiple testcases", [&]() {
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
