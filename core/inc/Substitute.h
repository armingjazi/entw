#pragma once
#include <unordered_map>

namespace entw {
template <typename T> class Substitute {
private:
  using FuncPtr = void (T::*)();
  struct HashKey {
    size_t operator()(FuncPtr funcPtr) const {
      static size_t i = 0;
      return i;
    }
  };

public:
  std::unordered_map<FuncPtr, size_t, HashKey> calls;

  void registerMethod(void (T::*memberFunc)()) {
    const auto call = calls.find(memberFunc);
    if (call != calls.end()) {
      const auto current = call->second;
      calls.erase(call);
      calls.emplace(memberFunc, current + 1);
    } else {
      calls.emplace(memberFunc, 1);
    }
  }
};
} // namespace entw