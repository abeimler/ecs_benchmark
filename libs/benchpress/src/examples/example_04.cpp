#define BENCHPRESS_CONFIG_MAIN
#include "benchpress/benchpress.hpp"

#include <chrono>

BENCHMARK("example bytes per second", [](benchpress::context* ctx) {
    ctx->set_bytes(1234567890);
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
})