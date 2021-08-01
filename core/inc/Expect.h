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
  CallExpectation<T> operator()(const Substitute<T> &s, void (T::*memberFunc)()) {
    assertionCount_ += 1;
    return CallExpectation<T>{s, memberFunc};
  };

  template <typename T>
  CallExpectationWithArg<T> operator()(const Substitute<T> &s, void (T::*memberFunc)(int)) {
    assertionCount_ += 1;
    return CallExpectationWithArg<T>{s, memberFunc};
  };

  size_t getAssertionCount() const;

private:
  size_t assertionCount_ = 0;
};
} // namespace entw
