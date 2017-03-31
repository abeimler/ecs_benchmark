/*
* Copyright (C) 2015 Christopher Gilbert.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/
#ifndef BENCHPRESS_HPP
#define BENCHPRESS_HPP

#include <algorithm>   // max, min
#include <atomic>      // atomic_intmax_t
#include <chrono>      // high_resolution_timer, duration
#include <functional>  // function
#include <iomanip>     // setw
#include <iostream>    // cout
#include <regex>       // regex, regex_match
#include <sstream>     // stringstream
#include <string>      // string
#include <thread>      // thread
#include <vector>      // vector
#include <memory>      // unique_ptr, make_unique
#include <map>         
#include <unordered_map>
#include <set>

namespace benchpress {

/*
 * The options class encapsulates all options for running benchmarks.
 *
 * When including benchpress, a main function can be emitted which includes a command-line parser for building an
 * options object. However from time-to-time it may be necessary for the developer to have to build their own main
 * stub and construct the options object manually.
 *
 * options opts;
 * opts
 *     .bench(".*")
 *     .benchtime(1)
 *     .cpu(4);
 */
class options {
    std::vector<std::string> d_bench;
    size_t      d_benchtime;
    size_t      d_cpu;
    bool        d_plotdata;
public:
    options()
        : d_bench( { ".*" } )
        , d_benchtime(1)
        , d_cpu(std::thread::hardware_concurrency())
        , d_plotdata(false)
    {}
    options& bench(const std::vector<std::string>& bench) {
        d_bench = bench;
        return *this;
    }
    options& benchtime(size_t benchtime) {
        d_benchtime = benchtime;
        return *this;
    }
    options& cpu(size_t cpu) {
        d_cpu = cpu;
        return *this;
    }
    options& plotdata(bool plotdata) {
        d_plotdata = plotdata;
        return *this;
    }
    std::vector<std::string> get_bench() const {
        return d_bench;
    }
    size_t get_benchtime() const {
        return d_benchtime;
    }
    size_t get_cpu() const {
        return d_cpu;
    }
    bool get_plotdata() const {
        return d_plotdata;
    }
};

class context;

/*
 * The benchmark_info class is used to store a function name / pointer pair.
 *
 * benchmark_info bi("example", [](benchpress::context* b) {
 *     // benchmark function
 * });
 */
class benchmark_info {
    std::string                         d_name;
    const std::function<void(context*)> d_func;

public:
    benchmark_info(std::string name, std::function<void(context*)> func)
        : d_name(name)
        , d_func(func)
    {}

    std::string                   get_name() const { return d_name; }
    std::function<void(context*)> get_func() const { return d_func; }
};

/*
 * The registration class is responsible for providing a single global point of reference for registering
 * benchmark functions.
 *
 * registration::get_ptr()->register_benchmark(info);
 */
class registration {
    std::vector<benchmark_info> d_benchmarks;

public:
    static registration* get_ptr() {
        static std::unique_ptr<registration> d_this = std::make_unique<registration>();
        return d_this.get();
    }

    void register_benchmark(benchmark_info& info) {
        d_benchmarks.push_back(info);
    }

    std::vector<benchmark_info> get_benchmarks() { return d_benchmarks; }
};

/*
 * The auto_register class is a helper used to register benchmarks.
 */
class auto_register {
public:
    auto_register(const std::string& name, std::function<void(context*)> func) {
        benchmark_info info(name, func);
        registration::get_ptr()->register_benchmark(info);
    }
};

#define CONCAT(x, y) x ## y
#define CONCAT2(x, y) CONCAT(x, y)
#ifdef __COUNTER__ 
#define REGISTER_NAME CONCAT2(__LINE__, __COUNTER__)
#else
#define REGISTER_NAME __LINE__
#endif

// The BENCHMARK macro is a helper for creating benchmark functions and automatically registering them with the
// registration class.
#define BENCHMARK(x, f) benchpress::auto_register CONCAT2(register_, REGISTER_NAME)((x), (f));


// This macro will prevent the compiler from removing a redundant code path which has no side-effects.
#define DISABLE_REDUNDANT_CODE_OPT() { asm(""); }

/*
 * This function can be used to keep variables on the stack that would normally be optimised away
 * by the compiler, without introducing any additional instructions or changing the behaviour of
 * the program.
 * 
 * This function uses the Extended Asm syntax of GCC. The volatile keyword indicates that the 
 * following instructions have some unknowable side-effect, and ensures that the code will neither 
 * be moved, nor optimised away.
 *
 * AssemblerTemplate: No operands.
 *
 * OutputOperands: None.
 *
 * InputOperands: The "g" is a wildcard constraint which tells the compiler that it may choose what 
 * to use for p (eg. a register OR a memory reference).
 *
 * Clobbers: The "memory" clobber tells the compiler that the assembly code performs reads or writes
 * to the memory pointed to by one of the input parameters.
 *
 * Example usage:
 *  std::vector<int> v;
 *  v.reserve(10);
 *  escape(v.data());
 */
#ifdef _MSC_VER

#pragma optimize("", off)

template <class T>
void escape(T&& datum)
{
  // see here: http://stackoverflow.com/questions/28287064/how-not-to-optimize-away-mechanics-of-a-folly-function
  datum = datum;
}

#pragma optimize("", on)

#else

inline void escape(void *p)
{
  asm volatile("" : : "g"(p) : "memory");
}

#endif

/*
 * This function can be used to disable the optimiser. It has the effect of creating a read / write
 * memory barrier for the compiler, meaning it does not assume that any values read from memory before
 * the asm remain unchanged after that asm; it reloads them as needed.
 *
 * Example usage:
 *  std::vector<int> v;
 *  v.reserve(10);
 *  escape(v.data());
 *  v.push_back(42);
 *  clobber(); // Ensure the integer pushed is read
 */
#ifdef _MSC_VER

inline void clobber()
{
  // see here: http://stackoverflow.com/questions/14449141/the-difference-between-asm-asm-volatile-and-clobbering-memory
  _ReadWriteBarrier();
}

#else

inline void clobber()
{
  asm volatile("" : : : "memory");
}

#endif

/*
 * The result class is responsible for producing a printable string representation of a benchmark run.
 */
class result {
    using fsec_t = std::chrono::duration<double>;
    using duration_t = std::chrono::nanoseconds;

    size_t                   d_num_iterations;
    std::chrono::nanoseconds d_duration;
    size_t                   d_num_bytes;

    std::string             d_name; 
    std::string             d_col;
    std::string             d_row;

public:
    result(size_t num_iterations, std::chrono::nanoseconds duration, size_t num_bytes)
        : d_num_iterations(num_iterations)
        , d_duration(duration)
        , d_num_bytes(num_bytes)
    {}

    void set_name(std::string name) {
        d_name = name;
    }
    std::string get_name() const { return d_name; }

    void set_col(std::string col) {
        d_col = col;
    }
    std::string get_col() const { return d_col; }

    void set_row(std::string row) {
        d_row = row;
    }
    std::string get_row() const { return d_row; }


    size_t get_ns_per_op() const {
        if (d_num_iterations <= 0) {
            return 0;
        }
        return std::chrono::duration_cast<std::chrono::nanoseconds>(d_duration).count() / d_num_iterations;
    }

    size_t get_ms_per_op() const {
        if (d_num_iterations <= 0) {
            return 0;
        }
        return std::chrono::duration_cast<std::chrono::milliseconds>(d_duration).count() / d_num_iterations;
    }

    double get_s_per_op() const {
        if (d_num_iterations <= 0) {
            return 0;
        }
        return std::chrono::duration_cast<fsec_t>(d_duration).count() / d_num_iterations;
    }

    double get_mb_per_s() const {
        if (d_num_iterations <= 0 || d_duration.count() <= 0 || d_num_bytes <= 0) {
            return 0;
        }
        return ((double(d_num_bytes) * double(d_num_iterations) / double(1e6)) /
                double(std::chrono::duration_cast<std::chrono::seconds>(d_duration).count()));
    }

    std::string to_string() const {
        std::stringstream tmp;
        tmp << std::setw(12) << std::right << d_num_iterations;

        size_t npo = get_ns_per_op();
        tmp << std::setw(18) << std::right << npo << std::setw(0) << " ns/op";

        size_t mpo = get_ms_per_op();
        if(mpo > 0){
            tmp << std::setw(14) << std::right << mpo << std::setw(0) << " ms/op";
        }

        double spo = get_s_per_op();
        if(spo > 0.01){
            tmp << std::setw(14) << std::right 
                << std::fixed << std::setprecision( 2 ) << spo
                << std::setw(0) << " s/op";
        }

        double mbs = get_mb_per_s();
        if (mbs > 0.0) {
            tmp << std::setw(14) << std::right << mbs << std::setw(0) << " MB/s";
        }

        return std::string(tmp.str());
    }
};

/*
 * The parallel_context class is responsible for providing a thread-safe context for parallel benchmark code.
 */
class parallel_context {
    std::atomic_intmax_t d_num_iterations;
public:
    parallel_context(size_t num_iterations)
        : d_num_iterations(num_iterations)
    {}

    bool next() {
        return (d_num_iterations.fetch_sub(1) > 0);
    }
};

/*
 * The context class is responsible for providing an interface for capturing benchmark metrics to benchmark functions.
 */
class context {
    bool                                           d_timer_on;
    std::chrono::high_resolution_clock::time_point d_start;
    std::chrono::nanoseconds                       d_duration;
    std::chrono::seconds                           d_benchtime;
    size_t                                         d_num_iterations;
    size_t                                         d_num_threads;
    size_t                                         d_num_bytes;
    benchmark_info                                 d_benchmark;

public:
    context(const benchmark_info& info, const options& opts)
        : d_timer_on(false)
        , d_start()
        , d_duration()
        , d_benchtime(std::chrono::seconds(opts.get_benchtime()))
        , d_num_iterations(1)
        , d_num_threads(opts.get_cpu())
        , d_num_bytes(0)
        , d_benchmark(info)
    {}

    size_t num_iterations() const { return d_num_iterations; }

    void set_num_threads(size_t n) { d_num_threads = n; }
    size_t num_threads() const { return d_num_threads; }

    void start_timer() {
        if (!d_timer_on) {
            d_start = std::chrono::high_resolution_clock::now();
            d_timer_on = true;
        }
    }
    void stop_timer() {
        if (d_timer_on) {
            d_duration += std::chrono::high_resolution_clock::now() - d_start;
            d_timer_on = false;
        }
    }
    void reset_timer() {
        if (d_timer_on) {
            d_start = std::chrono::high_resolution_clock::now();
        }
        d_duration = std::chrono::nanoseconds::zero();
    }

    void set_bytes(int64_t bytes) { d_num_bytes = bytes; }

    size_t get_ns_per_op() {
        if (d_num_iterations <= 0) {
            return 0;
        }
        return d_duration.count() / d_num_iterations;
    }

    void run_n(size_t n) {
        d_num_iterations = n;
        reset_timer();
        start_timer();
        d_benchmark.get_func()(this);
        stop_timer();
    }

    void run_parallel(std::function<void(parallel_context*)> f) {
        parallel_context pc(d_num_iterations);
        std::vector<std::thread> threads;
        for (size_t i = 0; i < d_num_threads; ++i) {
            threads.push_back(std::thread([&pc,&f]() -> void {
                f(&pc);
            }));
        }
        for(auto& thread : threads){
            thread.join();
        }
    }

    result run() {
        size_t n = 1;
        run_n(n);
        while (d_duration < d_benchtime && n < 1e9) {
            size_t last = n;
            if (get_ns_per_op() == 0) {
                n = static_cast<size_t>(1e9);
            } else {
                n = d_duration.count() / get_ns_per_op();
            }
            n = std::max(std::min(n+n/2, 100*last), last+1);
            n = round_up(n);
            run_n(n);
        }
        return result(n, d_duration, d_num_bytes);
    }

private:
    template<typename T>
    T round_down_10(T n) {
        int tens = 0;
        while (n > 10) {
            n /= 10;
            tens++;
        }
        int result = 1;
        for (int i = 0; i < tens; ++i) {
            result *= 10;
        }
        return result;
    }

    template<typename T>
    T round_up(T n) {
        T base = round_down_10(n);
        if (n < (2 * base)) {
            return 2 * base;
        }
        if (n < (5 * base)) {
            return 5 * base;
        }
        return 10 * base;
    }
};

#ifdef BENCHPRESS_CONFIG_MAIN

/*
 * The run_benchmarks function will run the registered benchmarks.
 */
void run_benchmarks(const options& opts) {
    using namespace std::string_literals;

    auto std_replace = [](std::string& str,
                const std::string& oldStr,
                const std::string& newStr) {
        std::string::size_type pos = 0u;
        while((pos = str.find(oldStr, pos)) != std::string::npos){
            str.replace(pos, oldStr.length(), newStr);
            pos += newStr.length();
        }
    };
    std::vector<result> results;

    for(std::string bench : opts.get_bench()){
        std::regex match_r(bench);

        auto benchmarks = registration::get_ptr()->get_benchmarks();

        std::string prefix = (opts.get_plotdata())? "## " : "";

        for (auto& info : benchmarks) {
            std::string name = info.get_name();
            if (std::regex_match(name, match_r)) {
                context c (info, opts);
                auto r = c.run();
                std::string rstr = r.to_string();
                std::cout << prefix << std::setw(64) << std::left << name << rstr << '\n';

                r.set_name(name);

                std::string col = bench;
                std_replace(col, ".*", "");
                std_replace(col, "\\s+", "");
                std_replace(col, " ", "");
                r.set_col(col);

                std::string tag;
                std::regex tag_regex (".*\\[\\s*(\\d+)\\s*\\].*");
                std::smatch tag_match;
                if (std::regex_match(name, tag_match, tag_regex)) {
                    if(tag_match.size() > 1){
                        tag = tag_match[1].str();
                    }
                }
                std::string row = tag;
                r.set_row(row);

                results.push_back(r);
            }
        }
    }

    if(opts.get_plotdata()) {
        std::cout << '\n';
        std::cout << "# plot data" << '\n';

        const int COL_WIDTH = 16;

        std::set<std::string> headers;
        std::map<std::string, std::map<std::string, std::string>> results_map;
        for(auto& result : results) {
            std::string name = result.get_name();

            std::string col = result.get_col();
            std::string row = result.get_row();
            std::string result_str = std::to_string(result.get_ns_per_op());
            result_str = (!result_str.empty())? result_str : "?"s;
            result_str = (!col.empty() && !row.empty())? result_str : "?"s;


            std::stringstream sort_col_ss;
            sort_col_ss << std::setw(COL_WIDTH) << std::setfill(' ') << std::right << col;
            std::string sort_col = sort_col_ss.str();
            
            std::stringstream sort_row_ss;
            sort_row_ss << std::setw(COL_WIDTH) << std::setfill(' ') << std::right << row;
            std::string sort_row = sort_row_ss.str();

            std::stringstream sort_result_ss;
            sort_result_ss << std::setw(COL_WIDTH) << std::setfill(' ') << std::right << result_str;
            std::string sort_result = sort_result_ss.str();


            headers.insert(sort_col);
            results_map[sort_row][sort_col] = sort_result;
        }

        //std::cout << "#### " << "[Debug] results_map result" << '\n';
        //for(const auto& r1 : results_map) {
        //    for(const auto& r2 : r1.second) {
        //        std::cout << "### " << r1.first << " " << r2.first << " " << r2.second << '\n'; 
        //    }
        //}

        if(!results_map.empty()) {
            std::cout << "# " << std::setw(COL_WIDTH) << std::right << std::setfill(' ') << ' ';
            for(const auto& header : headers) {
                std::cout << header;
            }
            std::cout << '\n';

            for(const auto& row_result : results_map) {
                const auto& row_left_header = row_result.first;
                const auto& row = row_result.second;

                if(!row_left_header.empty()) {
                    std::cout << "  " << row_left_header;

                    for(const auto& header : headers) {
                        const auto find_row_value = row.find(header);
                        if(find_row_value != std::end(row)) {
                            std::cout << find_row_value->second;
                        } else {
                            std::cout << std::setw(COL_WIDTH) << std::right << std::setfill(' ') << "?";
                        }
                    }

                    std::cout << '\n';
                }
            }
        }
        std::cout << '\n';
    }
}
#endif

} // namespace benchpress

/*
 * If BENCHPRESS_CONFIG_MAIN is defined when the file is included then a main function will be emitted which provides a
 * command-line parser and then executes run_benchmarks.
 */
#ifdef BENCHPRESS_CONFIG_MAIN
#include "cxxopts.hpp"
int main(int argc, char** argv) {
    std::chrono::high_resolution_clock::time_point bp_start = std::chrono::high_resolution_clock::now();
    benchpress::options bench_opts;
    try {
        cxxopts::Options cmd_opts(argv[0], " - command line options");
        cmd_opts.add_options()
            ("bench", "run benchmarks matching the regular expression", cxxopts::value<std::vector<std::string>>()
                ->default_value( { ".*" } ))
            ("benchtime", "run enough iterations of each benchmark to take t seconds", cxxopts::value<size_t>()
                ->default_value("1"))
            ("cpu", "specify the number of threads to use for parallel benchmarks", cxxopts::value<size_t>()
                ->default_value(std::to_string(std::thread::hardware_concurrency())))
            ("list", "list all available benchmarks")
            ("plotdata", "print plot data for gnuplot (use [tags] to tag the xlabel)")
            ("help", "print help")
        ;
        cmd_opts.parse(argc, argv);
        if (cmd_opts.count("help")) {
            std::cout << cmd_opts.help({""}) << '\n';
            exit(0);
        }
        if (cmd_opts.count("bench")) {
            bench_opts.bench(cmd_opts["bench"].as<std::vector<std::string>>());
        }
        if (cmd_opts.count("benchtime")) {
            bench_opts.benchtime(cmd_opts["benchtime"].as<size_t>());
        }
        if (cmd_opts.count("cpu")) {
            bench_opts.cpu(cmd_opts["cpu"].as<size_t>());
        }
        if (cmd_opts.count("plotdata")) {
            bench_opts.plotdata(true);
        }
        if (cmd_opts.count("list")) {
            auto benchmarks = benchpress::registration::get_ptr()->get_benchmarks();
            for (auto& info : benchmarks) {
                std::cout << info.get_name() << '\n';
            }
            exit(EXIT_SUCCESS);
        }
    } catch (const cxxopts::OptionException& e) {
        std::string prefix = (bench_opts.get_plotdata())? "## " : "";

        std::cout << prefix << "error parsing options: " << e.what() << '\n';
        exit(1);
    }
    std::string prefix = (bench_opts.get_plotdata())? "## " : "";

    benchpress::run_benchmarks(bench_opts);
    float duration = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::high_resolution_clock::now() - bp_start
    ).count() / 1000.f;
    std::cout << prefix << argv[0] << " " << duration << "s" << '\n';
    return 0;
}
#endif

#endif // BENCHPRESS_HPP
