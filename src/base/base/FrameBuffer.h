#ifndef ECS_BENCHMARKS_BASE_FRAMEBUFFER_H_
#define ECS_BENCHMARKS_BASE_FRAMEBUFFER_H_

#include <cstddef>
#include <cstdint>
#include <gsl/gsl-lite.hpp>
#include <utility>
#include <vector>

namespace ecs::benchmarks::base {

class FrameBuffer {
public:
  FrameBuffer(uint32_t w, uint32_t h) : m_width{w}, m_height{h}, m_buffer(gsl::narrow_cast<size_t>(m_width) * gsl::narrow_cast<size_t>(m_height)) {}

  [[nodiscard]] auto width() const noexcept { return m_width; }
  [[nodiscard]] auto height() const noexcept { return m_height; }

  void draw(int x, int y, char c) {
    if (y >= 0 && std::cmp_less(y, m_height)) {
      if (x >= 0 && std::cmp_less(x, m_width)) {
        m_buffer[gsl::narrow_cast<size_t>(x) + gsl::narrow_cast<size_t>(y) * m_width] = c;
      }
    }
  }

private:
  uint32_t m_width;
  uint32_t m_height;
  std::vector<char> m_buffer;
};

} // namespace ecs::benchmarks::base

#endif