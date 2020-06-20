#include <stdexcept>
#include <string>
#include <Substitute.h>

namespace entw {
template <typename T> class CallExpectation {
public:
  explicit CallExpectation(const Substitute<T> &substitute, void (T::*memberFunc)())
      : substitute_(substitute), memberFunc_(memberFunc){};

  void toHaveBeenCalled(std::size_t cardinality) noexcept(false) {

    const auto actualCardinality = substitute_.getCallCardinality(memberFunc_);

    if (actualCardinality == 0) {
      if (cardinality != 0) {
        throw std::logic_error("Call Cardinality does not match\nexpected\n " +
                               std::to_string(cardinality) + "\nreceived\n 0");
      }
    } else {
      if (actualCardinality != cardinality)
        throw std::logic_error("Call Cardinality does not match\nexpected\n " +
                               std::to_string(cardinality) + "\nreceived\n " +
                               std::to_string(actualCardinality));
    }
  }

private:
  const Substitute<T>& substitute_;
  void (T::*memberFunc_)();
};

template <typename T> class CallExpectationWithArg {
public:
  explicit CallExpectationWithArg(const Substitute<T> &substitute, void (T::*memberFunc)(int))
      : substitute_(substitute), memberFunc_(memberFunc){};


  void toHaveBeenCalledWith(size_t time, int arg) noexcept(false) {

    const auto actualArg = substitute_.getCallArguments(memberFunc_, time);

    if (actualArg != arg)
      throw std::logic_error("Call argument does not match\nexpected\n " +
          std::to_string(arg) + "\nreceived\n " +
          std::to_string(actualArg));

  }

private:
  const Substitute<T>& substitute_;
  void (T::*memberFunc_)(int);
};
} // namespace entw