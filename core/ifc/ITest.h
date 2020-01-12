#pragma once

namespace entw {
class ITest {
public:
  virtual ~ITest() = default;
  virtual ResultPtr operator()() = 0;
};
} // namespace entw