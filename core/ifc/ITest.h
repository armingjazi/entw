#pragma once
#include <memory>

namespace entw {
class ITest {
public:
  using TestMethod = std::function<void(Expect &expect) noexcept(false)>;

  virtual ~ITest() = default;
  virtual ResultPtr operator()() = 0;
};
using TestPtr = std::unique_ptr<ITest>;
} // namespace entw