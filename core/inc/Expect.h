#pragma once

namespace entw {
template<typename T>
class Expect {
 public:
  Expect operator()(const T& a) {
    Expect expect;
    expect.a_ = a;
    return expect;
  }

  bool toEqual(const T& a) {
    return this->a_ == a;
  }

 private:
  T a_;
};
}