# Command Line Options

## -bench _n_

Provide a regular expression selecting which benchmarks to run. The default value is `.*`, however any valid regex is
accepted by the runtime.

## -benchtime _n_

Provide a time value in seconds to choose how long benchmarks should run for. The default value is `1`, however larger
values provide increasingly significant statistical timing data.

## -cpu _n_

Provide a hint to the runtime to choose the number of threads to use in conjunction with `run_parallel`. The default is
the number of threads reported by the OS.

## -list

Print a newline delimited list of all registered benchmarks and exit.