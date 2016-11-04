#define BENCHPRESS_CONFIG_MAIN
#include "benchpress/benchpress.hpp"

#include <chrono>

BENCHMARK("multi-threaded example", [](benchpress::context* ctx) {
    ctx->run_parallel([](benchpress::parallel_context* pctx) {
        while (pctx->next()) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    });
})