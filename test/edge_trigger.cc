
#include <iostream>
#include <cassert>
#include <array>

#include "edge_trigger.hpp"

using lunarifish::edge_trigger;

enum class Output {
  kNoEdge = 0,
  kRisingEdge = 1,
  kFallingEdge = 2,
} output;

void test_bool() {
  constexpr std::array<std::pair<bool, Output>, 10> test_case = {
      {std::make_pair(true, Output::kNoEdge),
       std::make_pair(false, Output::kFallingEdge),
       std::make_pair(true, Output::kRisingEdge),
       std::make_pair(false, Output::kFallingEdge),
       std::make_pair(true, Output::kRisingEdge),
       std::make_pair(false, Output::kFallingEdge),
       std::make_pair(true, Output::kRisingEdge),
       std::make_pair(false, Output::kFallingEdge),
       std::make_pair(true, Output::kRisingEdge),
       std::make_pair(false, Output::kFallingEdge)}};

  bool var = true;
  auto et = edge_trigger<bool>(var)
                .on_rising([]() { output = Output::kRisingEdge; })
                .on_falling([]() { output = Output::kFallingEdge; });

  for (const auto& [test_val, expected_output] : test_case) {
    var = test_val;
    output = Output::kNoEdge;
    et.update();
    assert(output == expected_output);
  }
}

void test_int() {
  constexpr std::array<std::pair<int, Output>, 10> test_case = {
      {std::make_pair(10, Output::kNoEdge),
       std::make_pair(20, Output::kRisingEdge),
       std::make_pair(15, Output::kFallingEdge),
       std::make_pair(10, Output::kNoEdge),
       std::make_pair(20, Output::kRisingEdge),
       std::make_pair(15, Output::kFallingEdge),
       std::make_pair(10, Output::kNoEdge),
       std::make_pair(20, Output::kRisingEdge),
       std::make_pair(15, Output::kFallingEdge),
       std::make_pair(10, Output::kNoEdge)}};

  int var = 10;
  auto et = edge_trigger(var, 20, 15)
                .on_rising([]() { output = Output::kRisingEdge; })
                .on_falling([]() { output = Output::kFallingEdge; });

  for (const auto& [test_val, expected_output] : test_case) {
    var = test_val;
    output = Output::kNoEdge;
    et.update();
    assert(output == expected_output);
  }
}

void test_custom_type() {
  struct custom_type {
    int value;
    bool operator<(const custom_type& rhs) const { return value < rhs.value; }
    bool operator>(const custom_type& rhs) const { return value > rhs.value; }
    bool operator<=(const custom_type& rhs) const { return value <= rhs.value; }
    bool operator>=(const custom_type& rhs) const { return value >= rhs.value; }
  };

  constexpr std::array<std::pair<custom_type, Output>, 10> test_case = {
      {std::make_pair(custom_type{10}, Output::kNoEdge),
       std::make_pair(custom_type{20}, Output::kRisingEdge),
       std::make_pair(custom_type{15}, Output::kFallingEdge),
       std::make_pair(custom_type{10}, Output::kNoEdge),
       std::make_pair(custom_type{20}, Output::kRisingEdge),
       std::make_pair(custom_type{15}, Output::kFallingEdge),
       std::make_pair(custom_type{10}, Output::kNoEdge),
       std::make_pair(custom_type{20}, Output::kRisingEdge),
       std::make_pair(custom_type{15}, Output::kFallingEdge),
       std::make_pair(custom_type{10}, Output::kNoEdge)}};

  custom_type var{10};
  auto et = edge_trigger(var, custom_type{20}, custom_type{15})
                .on_rising([]() { output = Output::kRisingEdge; })
                .on_falling([]() { output = Output::kFallingEdge; });

  for (const auto& [test_val, expected_output] : test_case) {
    var = test_val;
    output = Output::kNoEdge;
    et.update();
    assert(output == expected_output);
  }
}

int main() {
  test_bool();
  test_int();
  test_custom_type();

}