#pragma once

#include "EqualityExpectation.h"
#include "Substitute.h"
#include "TestCase.h"

namespace entw {

class InterfaceToSubstitute {
public:
  virtual void methodWithNoArg() = 0;
  virtual void anotherMethodWithNoArg() = 0;
  virtual void methodWithOneArg(int arg) = 0;
  virtual void anotherMethodWithOneArg(int arg) = 0;
};

class SubstituteClass : public Substitute<SubstituteClass>,
                        public InterfaceToSubstitute {
public:
  void methodWithNoArg() override {
    registerMethod(&SubstituteClass::methodWithNoArg);
  }

  void anotherMethodWithNoArg() override {
    registerMethod(&SubstituteClass::anotherMethodWithNoArg);
  }

  void methodWithOneArg(int arg) override {
    registerMethod(&SubstituteClass::methodWithOneArg, arg);
  }

  void anotherMethodWithOneArg(int arg) override {
    registerMethod(&SubstituteClass::anotherMethodWithOneArg, arg);
  }
};

class SubstituteTestCase : public TestCase {
public:
  void include() override {
    test("tracks the cardinality of methods that have been called",
         [&](Expect &expect) {
           auto sub = SubstituteClass();

           sub.methodWithNoArg();

           expect(sub, &SubstituteClass::methodWithNoArg).toHaveBeenCalled(1);
         });

    test("gives untracked methods a cardinality of 0", [&](Expect &expect) {
      auto sub = SubstituteClass();

      expect(sub, &SubstituteClass::anotherMethodWithNoArg).toHaveBeenCalled(0);
    });

    test(
        "throws if method was called 0 cardinality was expected",
        [&](Expect expect) {
          auto sub = SubstituteClass();

          sub.methodWithNoArg();

          try {
            expect(sub, &SubstituteClass::methodWithNoArg).toHaveBeenCalled(0);
          } catch (const std::exception &e) {
            expect(std::string(e.what()))
                .toEqual(
                    std::string("Call Cardinality does not match\nexpected\n "
                                "0\nreceived\n 1"));
          }
        },
        0);

    test("tracks the cardinality of methods that have been called",
         [&](Expect &expect) {
           auto sub = SubstituteClass();

           sub.methodWithNoArg();
           sub.methodWithNoArg();

           expect(sub, &SubstituteClass::methodWithNoArg).toHaveBeenCalled(2);
         });

    test(
        "throws if cardinality of registered method was not matched",
        [&](Expect &expect) {
          auto sub = SubstituteClass();

          sub.methodWithNoArg();

          try {
            expect(sub, &SubstituteClass::methodWithNoArg).toHaveBeenCalled(2);
          } catch (const std::exception &e) {
            expect(std::string(e.what()))
                .toEqual(
                    std::string("Call Cardinality does not match\nexpected\n "
                                "2\nreceived\n 1"));
          }
        },
        2);

    test("tracks the argument of methods", [&](Expect &expect) {
      auto sub = SubstituteClass();

      sub.methodWithOneArg(10);

      expect(sub, &SubstituteClass::methodWithOneArg)
          .toHaveBeenCalledWith(0, 10);
    });

    test(
        "tracks the argument of methods for multiple calls",
        [&](Expect &expect) {
          auto sub = SubstituteClass();

          sub.methodWithOneArg(10);

          sub.methodWithOneArg(12);

          expect(sub, &SubstituteClass::methodWithOneArg)
              .toHaveBeenCalledWith(0, 10);

          expect(sub, &SubstituteClass::methodWithOneArg)
              .toHaveBeenCalledWith(1, 12);
        },
        2);

    test(
        "throws for non matching arguments with actual call",
        [&](Expect &expect) {
          auto sub = SubstituteClass();

          sub.methodWithOneArg(10);

          sub.methodWithOneArg(12);

          try {
            expect(sub, &SubstituteClass::methodWithOneArg)
                .toHaveBeenCalledWith(0, 12);
          } catch (const std::exception &e) {
            expect(std::string(e.what()))
                .toEqual(std::string("Call argument does not match\nexpected\n "
                                     "12\nreceived\n 10"));
          }
        },
        2);

    test(
        "throws for mismatched call number for registered call",
        [&](Expect &expect) {
          auto sub = SubstituteClass();

          sub.methodWithOneArg(10);

          try {
            expect(sub, &SubstituteClass::methodWithOneArg)
                .toHaveBeenCalledWith(1, 10);
          } catch (const std::exception &e) {
            expect(std::string(e.what()))
                .toEqual("the method was called only 1 times you are asking "
                         "for 2th call");
          }
        },
        2);

    test(
        "tracks call numbers for multiple methods",
        [&](Expect &expect) {
          auto sub = SubstituteClass();

          sub.methodWithOneArg(10);
          sub.anotherMethodWithOneArg(22);

          expect(sub, &SubstituteClass::methodWithOneArg)
              .toHaveBeenCalledWith(0, 10);
          expect(sub, &SubstituteClass::anotherMethodWithOneArg)
              .toHaveBeenCalledWith(0, 22);
        },
        2);

    test(
        "throws if the argument was not matched",
        [&](Expect &expect) {
          auto sub = SubstituteClass();

          sub.methodWithOneArg(10);

          try {
            expect(sub, &SubstituteClass::methodWithOneArg)
                .toHaveBeenCalledWith(0, 11);
          } catch (const std::exception &e) {
            expect(std::string(e.what()))
                .toEqual(std::string("Call argument does not match\nexpected\n "
                                     "11\nreceived\n 10"));
          }
        },
        2);
  }
};
} // namespace entw