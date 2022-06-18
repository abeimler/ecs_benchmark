#ifndef ECS_BENCHMARKS_BASICBENCHMARK_H_
#define ECS_BENCHMARKS_BASICBENCHMARK_H_

#include <utility>
#include <vector>
#include <algorithm>
#include <string>
#include <optional>

#include <benchmark/benchmark.h>

namespace ecs::benchmarks::base {

    template<size_t N>
    struct StringLiteral {
        /*implicit*/ constexpr StringLiteral(const char (&str)[N]) {
            std::copy_n(str, N, value);
            value[N] = '\0';
        }

        char value[N + 1];
    };

    struct ESCBenchmarkOptions {
        bool add_more_complex_system{false};
        std::optional<std::string> version;
    };

    struct ComponentsCounter {
        size_t component_one_count{0};
        size_t component_two_count{0};
        size_t component_three_count{0};
    };

    inline static constexpr auto MIN_ENTITIES_RANGE = 8L;
    inline static constexpr auto MAX_ENTITIES_RANGE = 2'097'152L;

    void BEDefaultArguments(benchmark::internal::Benchmark* b);
}

#endif //ECS_BENCHMARKS_BASICBENCHMARK_H_
