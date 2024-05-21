
#ifndef LUNARIFISH_EDGE_TRIGGER_HPP
#define LUNARIFISH_EDGE_TRIGGER_HPP

#if __cplusplus >= 201703L  // minimum C++17

#include <functional>
#include <list>

namespace lunarifish {

template <typename T, typename = void>
struct is_comparable : std::false_type {};

template <typename T>
struct is_comparable<
    T, std::void_t<decltype(std::declval<T>() < std::declval<T>(),
                            std::declval<T>() > std::declval<T>(),
                            std::declval<T>() <= std::declval<T>(),
                            std::declval<T>() >= std::declval<T>())>>
    : std::true_type {};

template <typename T>
constexpr bool is_comparable_v = is_comparable<T>::value;

template <typename T,
          typename enable_if_comparable = std::enable_if_t<is_comparable_v<T>>>
class edge_trigger {
 public:
  edge_trigger(T& variable, T rising_threshold, T falling_threshold)
      : variable_(variable),
        rising_threshold_(rising_threshold),
        falling_threshold_(falling_threshold) {
    if (variable > rising_threshold) {
      state_ = true;
    } else {
      state_ = false;
    }
  }

  template <typename U = T, std::enable_if_t<std::is_same_v<U, bool>, int> = 0>
  explicit edge_trigger(U& var)
      : variable_(var), rising_threshold_(true), falling_threshold_(false) {
    if (variable_) {
      state_ = true;
    } else {
      state_ = false;
    }
  }

  edge_trigger& on_rising(const std::function<void()>& callback) {
    rising_edge_callbacks_.emplace_back(callback);
    return *this;
  }

  edge_trigger& on_falling(const std::function<void()>& callback) {
    falling_edge_callbacks_.emplace_back(callback);
    return *this;
  }

  void update() {
    if (variable_ >= rising_threshold_ && !state_) {
      state_ = true;
      for (const auto& callback : rising_edge_callbacks_) {
        callback();
      }
    } else if (variable_ <= falling_threshold_ && state_) {
      state_ = false;
      for (const auto& callback : falling_edge_callbacks_) {
        callback();
      }
    }
  }

 private:
  bool state_;
  T& variable_;
  T rising_threshold_;
  T falling_threshold_;
  std::list<std::function<void()>> rising_edge_callbacks_{};
  std::list<std::function<void()>> falling_edge_callbacks_{};
};

#endif

}  // namespace lunarifish

#endif  // LUNARIFISH_EDGE_TRIGGER_HPP
