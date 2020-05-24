#pragma once

#include "CallExpectation.h"
#include "EqualityExpectation.h"

namespace entw {
class Expect {
public:
  template <typename T> EqualityExpectation<T> operator()(const T &a) {
    assertionCount_ += 1;
    return EqualityExpectation<T>{a};
  };

  template <typename T>
  CallExpectation<T> operator()(const T &object, void (T::*memberFunc)()) {
    assertionCount_ += 1;
    return CallExpectation<T>{object, memberFunc};
  };

  size_t getAssertionCount() const;

private:
  size_t assertionCount_ = 0;
};
} // namespace entw
