#define BENCHPRESS_CONFIG_MAIN
#include "benchpress/benchpress.hpp"

unsigned int fib(unsigned int n) {
    return n < 2 ? n : fib(n-1) + fib(n-2);
}

BENCHMARK("fib 0", [](benchpress::context* ctx) {
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        auto f = fib(0);
        benchpress::escape(&f);
    }
})

BENCHMARK("fib 5", [](benchpress::context* ctx) {
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        auto f = fib(5);
        benchpress::escape(&f);
    }
})

BENCHMARK("fib 10", [](benchpress::context* ctx) {
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        auto f = fib(10);
        benchpress::escape(&f);
    }
})

BENCHMARK("fib 15", [](benchpress::context* ctx) {
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        auto f = fib(15);
        benchpress::escape(&f);
    }
})

BENCHMARK("fib 20", [](benchpress::context* ctx) {
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        auto f = fib(20);
        benchpress::escape(&f);
    }
})