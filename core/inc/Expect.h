#pragma once

#include <string>

namespace entw {
template <typename T> class Expect {
public:
  explicit Expect(const T &a) : a_(a){};

  void toEqual(const T &a) noexcept(false) {
    if (this->a_ != a) {
      throw std::logic_error("expected\n " + std::to_string(a) + "\nreceived\n " +
                             std::to_string(this->a_));
    }
  }

private:
  T a_;
};

template <typename T> Expect<T> expect(const T &a) { return Expect<T>{a}; };

template <> void Expect<std::string>::toEqual(const std::string &a) {
  if (this->a_ != a) {
    throw std::logic_error(
        std::string("expected\n " + a + "\nreceived\n " + this->a_));
  }
}
} // namespace entw
