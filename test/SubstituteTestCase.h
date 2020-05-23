#pragma once

#include <Expect.h>
#include <Substitute.h>
#include <TestCase.h>

namespace entw {

class Interface {
public:
  virtual void methodWithNoArg() = 0;
  virtual void anotherMethodWithNoArg() = 0;
};

class SubstituteInterface : public Substitute<SubstituteInterface>,
                            public Interface {
public:
  void methodWithNoArg() override {
    registerMethod(&SubstituteInterface::methodWithNoArg);
  }
  void anotherMethodWithNoArg() override {
    registerMethod(&SubstituteInterface::anotherMethodWithNoArg);
  }
};

class SubstituteTestCase : public TestCase {
public:
  void include() override {
    it("tracks the cardinality of methods that will be called", [&]() {
      auto sub = SubstituteInterface();

      sub.methodWithNoArg();

      expect(sub, &SubstituteInterface::methodWithNoArg)
          .toHaveBeenCalled(1);
    });

    it ("gives untracked methods a cardinality of 0", [&]() {
      auto sub = SubstituteInterface();

      expect(sub, &SubstituteInterface::anotherMethodWithNoArg)
          .toHaveBeenCalled(0);
    });

    it ("throws if method was called but cardinality was 0", [&]() {
      auto sub = SubstituteInterface();

      sub.methodWithNoArg();

      try {
        expect(sub, &SubstituteInterface::methodWithNoArg)
            .toHaveBeenCalled(0);
      } catch (const std::exception &e) {
        expect(std::string(e.what()))
            .toEqual(std::string("Call Cardinality does not match\nexpected\n "
                                 "0\nreceived\n 1"));
      }

    });

    it("tracks the cardinality of methods that will be called", [&]() {
      auto sub = SubstituteInterface();

      sub.methodWithNoArg();
      sub.methodWithNoArg();

      expect(sub, &SubstituteInterface::methodWithNoArg)
          .toHaveBeenCalled(2);
    });


    it("throws if cardinality of registered method was not matched", [&]() {
      auto sub = SubstituteInterface();

      sub.methodWithNoArg();

      try {
        expect(sub, &SubstituteInterface::methodWithNoArg)
            .toHaveBeenCalled(2);
      } catch (const std::exception &e) {
        expect(std::string(e.what()))
            .toEqual(std::string("Call Cardinality does not match\nexpected\n "
                                 "2\nreceived\n 1"));
      }
    });
  }
};
} // namespace entw