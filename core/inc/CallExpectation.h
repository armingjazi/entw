#include <stdexcept>
#include <string>

template <typename T> class CallExpectation {
public:
  explicit CallExpectation(const T &object, void (T::*memberFunc)())
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