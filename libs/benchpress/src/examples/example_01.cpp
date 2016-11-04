#define BENCHPRESS_CONFIG_MAIN
#include "benchpress/benchpress.hpp"

#include <chrono>
#include <iostream>

BENCHMARK("example", [](benchpress::context* ctx) {
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        std::cout << "hello" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
})