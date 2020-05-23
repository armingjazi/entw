#pragma once

#include <Substitute.h>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>

template <typename T> struct is_string { static const bool value = false; };

template <class T, class Traits, class Alloc>
struct is_string<std::basic_string<T, Traits, Alloc>> {
  static const bool value = true;
};

template <typename T> struct is_printable {
  static const bool value = is_string<T>::value || std::is_pointer<T>::value;
};

namespace entw {
template <typename T> class Expect {
public:
  explicit Expect(const T &a) : a_(a){};

  using DummyType = void;

  template <typename U = T,
            typename std::enable_if<!std::is_arithmetic<U>::value &&
                                        !is_printable<U>::value,
                                    DummyType>::type * = nullptr>
  std::string what(const U &expected, const U &actual) {
    return std::string("expected equal values received non equal values");
  }

  template <typename U = T,
            typename std::enable_if<!std::is_arithmetic<U>::value &&
                                        !is_printable<U>::value,
                                    DummyType>::type * = nullptr>
  std::string notWhat(const U &value) {
    return std::string("expected non equal values received equal values");
  }

  template <typename U = T,
            typename std::enable_if<std::is_arithmetic<U>::value,
                                    DummyType>::type * = nullptr>
  std::string what(const U &expected, const U &actual) {
    return std::string("expected\n " + std::to_string(expected) +
                       "\nreceived\n " + std::to_string(actual));
  }

  template <typename U = T,
            typename std::enable_if<is_printable<U>::value, DummyType>::type * =
                nullptr>
  std::string what(const U &expected, const U &actual) {
    std::stringstream result;
    result << "expected\n " << expected << "\nreceived\n " << actual;
    return result.str();
  }

  template <typename U = T,
            typename std::enable_if<std::is_arithmetic<U>::value,
                                    DummyType>::type * = nullptr>
  std::string notWhat(const U &value) {
    return std::string("expected different values\nreceived equal values\n" +
                       std::to_string(value));
  }

  template <typename U = T,
            typename std::enable_if<is_printable<U>::value, DummyType>::type * =
                nullptr>
  std::string notWhat(const U &value) {
    std::stringstream result;
    result << "expected different values\nreceived equal values\n" << value;
    return result.str();
  }

  void notToEqual(const T &a) noexcept(false) {
    if (!(this->a_ != a)) {
      throw std::logic_error(notWhat(a));
    }
  }

  void toEqual(const T &a) noexcept(false) {
    if (!(this->a_ == a)) {
      throw std::logic_error(what(a, this->a_));
    }
  }

private:
  T a_;
};

template <typename T> Expect<T> expect(const T &a) { return Expect<T>{a}; }

template <typename T> class CallExpect {
public:
  explicit CallExpect(const T &object, void (T::*memberFunc)())
      : object_(object), memberFunc_(memberFunc){};

  void toHaveBeenCalled(std::size_t cardinality) noexcept(false) {
    const auto call = object_.calls.find(memberFunc_);

    if (call == object_.calls.end()) {
      if (cardinality != 0) {
        throw std::logic_error("Call Cardinality does not match\nexpected\n " +
                               std::to_string(cardinality) + "\nreceived\n 0");
      }
    } else {
      if (call->second != cardinality)
        throw std::logic_error("Call Cardinality does not match\nexpected\n " +
                               std::to_string(cardinality) + "\nreceived\n " +
                               std::to_string(call->second));
    }
  }
private:
  T object_;
  void (T::*memberFunc_)();
};

template <typename T>
CallExpect<T> expect(const T &object, void (T::*memberFunc)()) {
  return CallExpect<T>{object, memberFunc};
}

} // namespace entw
