#pragma once
#include "EqualityExpectation.h"
#include "TestCase.h"
#include <cassert>
#include <iostream>

namespace entw {
class ExpectTestCase : public TestCase {
public:
  void include() override {
    test("expects success for equal number",
         [&](Expect &expect) { expect(50).toEqual(50); });

    test("expects failure for non equal numbers", [&](Expect &expect) {
      try {
        expect(50).toEqual(51);
      } catch (const std::exception &e) {
        assert(std::string(e.what()) ==
            std::string("expected\n 51\nreceived\n 50"));
      }
    });

    test("expects success for equal string", [&](Expect &expect) {
      expect(std::string("test")).toEqual(std::string("test"));
    });

    test("expects failure for non equal string", [&](Expect &expect) {
      try {
        expect(std::string("badString")).toEqual(std::string("goodString"));
      } catch (const std::exception &e) {
        assert(std::string(e.what()) ==
            "expected\n goodString\nreceived\n badString");
      }
    });

    test("expects success equal pointers", [&](Expect &expect) {
      class Cat {
        int meow = 0;
      };

      const auto data = Cat();
      const auto pointerToCat = &data;

      expect(&data).toEqual(pointerToCat);
    });

    test("expects fail with non equal pointers", [&](Expect &expect) {
      class Cat {
        int meow = 0;
      };

      const auto first_cat = Cat();
      const auto second_cat = Cat();

      try {
        expect(&first_cat).toEqual(&second_cat);
      } catch (const std::exception &e) {

        assert(std::string(e.what()).find("expected") != std::string::npos);
        assert(std::string(e.what()).find("received") != std::string::npos);
      }
    });

    test("supports not semantics",
         [&](Expect &expect) { expect(50).notToEqual(51); });

    test("expects failure for equal numbers", [&](Expect &expect) {
      try {
        expect(50).notToEqual((50));
      } catch (const std::exception &e) {
        assert(std::string(e.what()) ==
            std::string(
                "expected different values\nreceived equal values\n50"));
      }
    });

    test("expects failure for equal strings", [&](Expect &expect) {
      try {
        expect(std::string("test")).notToEqual((std::string("test")));
      } catch (const std::exception &e) {
        assert(std::string(e.what()) ==
            std::string(
                "expected different values\nreceived equal values\ntest"));
      }
    });

    test("expects success with equal objects", [&](Expect &expect) {
      class Comparable {
      public:
        bool operator==(const Comparable &comp) { return true; }
      };

      const auto comparable = Comparable();

      expect(comparable).toEqual(comparable);
    });

    test("expects success with non equal objects", [&](Expect &expect) {
      class Comparable {
      public:
        bool operator!=(const Comparable &comp) { return true; }
      };

      const auto comparable = Comparable();

      expect(comparable).notToEqual(comparable);
    });
  }
};
} // namespace entw
