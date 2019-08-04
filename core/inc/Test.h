#include <utility>

#pragma once

#include <functional>

namespace entw {
class Test {
 public:
  using signature = std::function<bool(void)>;

  Test(std::string name, const signature &function)
      : name_(std::move(name)),
        function_(std::move(function)) {
  }

  std::string name() {
    return name_;
  }

  bool operator()() {
    return function_();
  }

 private:
  std::string name_;
  std::function<bool(void)> function_;
};
} // namespace entw