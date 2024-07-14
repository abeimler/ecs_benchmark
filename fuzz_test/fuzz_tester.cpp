#include <format>
#include <iostream>
#include <iterator>
#include <utility>
#include <cstdint>

[[nodiscard]] auto sum_values(const uint8_t* Data, size_t Size) {
  constexpr auto scale = 1000;

  int value = 0;
  for (std::size_t offset = 0; offset < Size; ++offset) {
    value += static_cast<int>(*std::next(Data, static_cast<long>(offset))) * scale;
  }
  return value;
}

// Fuzzer that attempts to invoke undefined behavior for signed integer overflow
extern "C" int LLVMFuzzerTestOneInput(const uint8_t* Data, size_t Size) {
  std::cout << std::format("Value sum: {}, len{}\n", sum_values(Data, Size), Size);
  return 0;
}