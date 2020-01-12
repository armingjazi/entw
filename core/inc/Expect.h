#pragma once

namespace entw {
template <typename T> class Expect {
public:
  explicit Expect(const T &a) : a_(a){};

  bool toEqual(const T &a) { return this->a_ == a; }

private:
  T a_;
};

template <typename T> Expect<T> expect(const T &a) { return Expect<T>{a}; };
}