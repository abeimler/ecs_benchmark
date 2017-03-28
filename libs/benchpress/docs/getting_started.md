# Getting Started

## Writing benchmarks

A simple benchmark looks like this:

```cpp
BENCHMARK("example", [](benchpress::context* ctx) {
	for (size_t i = 0; i < ctx->num_iterations(); ++i) {
		std::cout << "hello" << std::endl;
	}
})
```

Every benchmark function is passed a parameter `benchpress::context*`. The target code must be executed n 
(`benchpress::context::num_iterations()`) times. The value n is adjusted until the benchmark runs long enough to be 
timed reliably.

The example will produce the following output:

```
example          1000000        1165 ns/op
```

The output shows that the code was run 1000000 times, and each cycle lasted 1165 nanoseconds.

If a benchmark performs some expensive setup before running the timer may be reset:

```cpp
BENCHMARK("expensive setup", [](benchpress::context* ctx) {
	setup_expensive();
	ctx->reset_timer();
	for (size_t i = 0; i < ctx->num_iterations(); ++i) {
		test_func();
	}
})
```

If a benchmark needs to check performance in a parallel setting, it may use the run_parallel helper function, which is
intended to be used with the -cpu command line option.

```cpp
BENCHMARK("parallel benchmark", [](benchpress::context* ctx) {
	ctx->run_parallel([](benchpress::parallel_context* pctx) {
		while (pctx->next()) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
		}
	}
})
```
