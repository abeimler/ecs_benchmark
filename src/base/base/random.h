/******************************************************************************
The MIT License(MIT)

Embedded Template Library.
https://github.com/ETLCPP/etl
https://www.etlcpp.com

Copyright(c) 2017 jwellbelove

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files(the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
******************************************************************************/

#ifndef ECS_BENCHMARKS_BASE_RANDOM_H_
#define ECS_BENCHMARKS_BASE_RANDOM_H_

#include <array>
#include <bit>
#include <cmath>
#include <cstdint>
#include <limits>

namespace ecs::benchmarks::base {

/*  Written in 2018 by David Blackman and Sebastiano Vigna (vigna@acm.org)

To the extent possible under law, the author has dedicated all copyright
and related and neighboring rights to this software to the public domain
worldwide. This software is distributed without any warranty.

See <http://creativecommons.org/publicdomain/zero/1.0/>. */
class random_xoshiro128 {
public:
  //***************************************************************************
  /// Default constructor.
  /// Attempts to come up with a unique non-zero seed.
  //***************************************************************************
  random_xoshiro128() noexcept {
    // An attempt to come up with a unique non-zero seed,
    // based on the address of the instance.
    const auto n = std::bit_cast<uintptr_t>(this);
    const auto seed = static_cast<uint32_t>(n);
    initialise(seed);
  }

  //***************************************************************************
  /// Constructor with seed value.
  ///\param seed The new seed value.
  //***************************************************************************
  constexpr explicit random_xoshiro128(uint32_t seed) noexcept { initialise(seed); }

  //***************************************************************************
  /// Initialises the sequence with a new seed value.
  ///\param seed The new seed value.
  //***************************************************************************
  constexpr void initialise(uint32_t seed) noexcept {
    // Add the first four primes to ensure that the seed isn't zero.
    state[0] = seed + 3;
    state[1] = seed + 5;
    state[2] = seed + 7;
    state[3] = seed + 11;
  }

  constexpr explicit random_xoshiro128(const std::array<uint32_t, 4>& s) : state(s) {}

  //***************************************************************************
  /// Get the next random_xoshiro128 number.
  //***************************************************************************
  constexpr uint32_t operator()() noexcept { return next(); }

  //***************************************************************************
  /// Get the next random_xoshiro128 number in a specified inclusive range.
  //***************************************************************************
  constexpr uint32_t range(uint32_t low, uint32_t high) noexcept {
    const uint32_t r = high - low + 1;
    return (operator()() % r) + low;
  }

  constexpr inline uint32_t range_max() noexcept {
    return range(std::numeric_limits<uint32_t>::min(), std::numeric_limits<uint32_t>::max());
  }

  constexpr inline uint32_t range_min(uint32_t min) noexcept {
    return range(min, std::numeric_limits<uint32_t>::max());
  }

public:
  std::array<uint32_t, 4> state;

private:
  /* This is xoshiro128** 1.1, one of our 32-bit all-purpose, rock-solid
     generators. It has excellent speed, a state size (128 bits) that is
     large enough for mild parallelism, and it passes all tests we are aware
     of.

     Note that version 1.0 had mistakenly s[0] instead of s[1] as state
     word passed to the scrambler.

     For generating just single-precision (i.e., 32-bit) floating-point
     numbers, xoshiro128+ is even faster.

     The state must be seeded so that it is not everywhere zero. */

  static inline constexpr uint32_t rotl(const uint32_t x, int k) noexcept { return (x << k) | (x >> (32 - k)); }

  constexpr uint32_t next() noexcept {
    const uint32_t result = rotl(state[1] * 5, 7) * 9;

    const uint32_t t = state[1] << 9;

    state[2] ^= state[0];
    state[3] ^= state[1];
    state[1] ^= state[2];
    state[0] ^= state[3];

    state[2] ^= t;

    state[3] = rotl(state[3], 11);

    return result;
  }


  /* This is the jump function for the generator. It is equivalent
    to 2^64 calls to next(); it can be used to generate 2^64
    non-overlapping subsequences for parallel computations. */
  /*
  constexpr void jump() noexcept {
    constexpr uint32_t JUMP[] = {0x8764000b, 0xf542d2d3, 0x6fa035c3, 0x77f2db5b};

    uint32_t s0 = 0;
    uint32_t s1 = 0;
    uint32_t s2 = 0;
    uint32_t s3 = 0;
    for (size_t i = 0; i < sizeof JUMP / sizeof *JUMP; i++) {
      for (size_t b = 0; b < 32; b++) {
        if (JUMP[i] & UINT32_C(1) << b) {
          s0 ^= state[0];
          s1 ^= state[1];
          s2 ^= state[2];
          s3 ^= state[3];
        }
        next();
      }
    }

    state[0] = s0;
    state[1] = s1;
    state[2] = s2;
    state[3] = s3;
  }
  */


  /* This is the long-jump function for the generator. It is equivalent to
    2^96 calls to next(); it can be used to generate 2^32 starting points,
    from each of which jump() will generate 2^32 non-overlapping
    subsequences for parallel distributed computations. */
  /*
  constexpr void long_jump() noexcept {
    constexpr uint32_t LONG_JUMP[] = {0xb523952e, 0x0b6f099f, 0xccf5a0ef, 0x1c580662};

    uint32_t s0 = 0;
    uint32_t s1 = 0;
    uint32_t s2 = 0;
    uint32_t s3 = 0;
    for (size_t i = 0; i < sizeof LONG_JUMP / sizeof *LONG_JUMP; i++) {
      for (size_t b = 0; b < 32; b++) {
        if (LONG_JUMP[i] & UINT32_C(1) << b) {
          s0 ^= state[0];
          s1 ^= state[1];
          s2 ^= state[2];
          s3 ^= state[3];
        }
        next();
      }
    }

    state[0] = s0;
    state[1] = s1;
    state[2] = s2;
    state[3] = s3;
  }
  */
};

} // namespace ecs::benchmarks::base

#endif