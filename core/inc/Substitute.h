#pragma once
#include <string>
#include <unordered_map>
#include <vector>

namespace entw {
template <typename T> class Substitute {
public:
  using FuncPtr = void (T::*)();
  using FuncPtrWithOneArg = void (T::*)(int);

  struct TimeArg {
    size_t time;
    size_t arg;
  };

  struct HashKey {
    size_t operator()(FuncPtr funcPtr) const {
      static size_t i = 0;
      return i;
    }

    size_t operator()(FuncPtrWithOneArg funcPtr) const {
      static size_t i = 0;
      return i;
    }
  };

  using funcMap = std::unordered_map<FuncPtr, size_t, HashKey>;
  using funcMapWithOneArg = std::vector<std::pair<FuncPtrWithOneArg, int>>;

  void registerMethod(void (T::*memberFunc)()) {
    const auto call = calls_.find(memberFunc);
    if (call != calls_.end()) {
      const auto current = call->second;
      calls_.erase(call);
      calls_.emplace(memberFunc, current + 1);
    } else {
      calls_.emplace(memberFunc, 1);
    }
  }

  void registerMethod(void (T::*memberFunc)(int), int arg) {
    callsWithOneArg_.emplace_back(std::make_pair(memberFunc, arg));
  }

  size_t getCallCardinality(FuncPtr func) const {
    const auto call = this->calls_.find(func);

    if (call == this->calls_.end())
      return 0;

    return call->second;
  }

  int getCallArguments(FuncPtrWithOneArg func, size_t time) const noexcept(false) {
    try {
      auto callsToFunc = std::vector<int>();
      for (auto it = this->callsWithOneArg_.begin();
           it != this->callsWithOneArg_.end(); ++it) {
        if (it->first == func)
          callsToFunc.emplace_back(it->second);
      }

      return callsToFunc.at(time);

    } catch (const std::out_of_range &) {
      throw std::logic_error("the method was called only " +
                             std::to_string(this->callsWithOneArg_.size()) +
                             " times" + " you are asking for " +
                             std::to_string(time + 1) + "th call");
    }
  }

private:
  funcMap calls_;
  funcMapWithOneArg callsWithOneArg_;
};
} // namespace entw