# Reference

## benchpress::context

### size_t num_iterations()

Get the number of iterations to run the benchmark function. It is important for a benchmark to execute the benchmark
function this many times.

```cpp
BENCHMARK("example") {
    for (size_t i = 0; i < b->num_iterations(); ++i) {
        // run benchmark function ...
    }
}
```

### void set_num_threads(size_t n)

Set the number of threads to be used with `run_parallel`.

### size_t num_threads()

Get the number of threads spawned by `run_parallel`.

### void start_timer()

Starts timing. If the timer is already running then this function will do nothing.

### void stop_timer()

Stops timing. If the timer is already stopped then this function will do nothing. Can be useful for only timing certain
parts of code.

### void reset_timer()

Resets the timer. Can be useful for excluding expensive setup code.

### void set_bytes(int64_t bytes)

When called, benchpress will collect information about how much data the benchmark function processes per second, and
print additional result data for the benchmark function.

### size_t get_ns_per_op()

Returns the average number of nanoseconds elapsed per cycle of the benchmark function.

### void run_parallel(std::function<void(benchpress::parallel_context*)> f)

When called, benchpress will launch `num_threads()` threads and execute the function `f`.

## benchpress::parallel_context

### bool next()

Returns true until there is no more work to do, when the function will return false. Thread safe. Example:

```cpp
BENCHMARK("multi-threaded example") {
    b->run_parallel([](benchpress::parallel_context* pb) {
        while (pb->next()) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    });
}
```

## void benchpress::escape(void *p)

This function can be used to keep variables on the stack that would normally be optimised away
by the compiler, without introducing any additional instructions or changing the behaviour of
the program.

```cpp
std::vector<int> v;
v.reserve(10);
escape(v.data());
```

## void benchpress::clobber()

This function can be used to disable the optimiser. It has the effect of creating a read / write
memory barrier for the compiler, meaning it does not assume that any values read from memory before
the asm remain unchanged after that asm; it reloads them as needed.

```cpp
std::vector<int> v;
v.reserve(10);
escape(v.data());
v.push_back(42);
clobber(); // Ensure the integer pushed is read
```