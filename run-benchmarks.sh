#!/usr/bin/env bash

#./build.sh

./cmake-build-relwithdebinfo/benchmark/benchmarks/entt/ecs-benchmark-entt --benchmark_format=json > ./reports/entt.json
./cmake-build-relwithdebinfo/benchmark/benchmarks/entityx/ecs-benchmark-entityx --benchmark_format=json > ./reports/entityx.json
./cmake-build-relwithdebinfo/benchmark/benchmarks/ginseng/ecs-benchmark-ginseng --benchmark_format=json > ./reports/ginseng.json
./cmake-build-relwithdebinfo/benchmark/benchmarks/mustache/ecs-benchmark-mustache --benchmark_format=json > ./reports/mustache.json
./cmake-build-relwithdebinfo/benchmark/benchmarks/openecs/ecs-benchmark-openecs --benchmark_format=json > ./reports/openecs.json
./cmake-build-relwithdebinfo/benchmark/benchmarks/flecs/ecs-benchmark-flecs --benchmark_format=json > ./reports/openflecsecs.json

./cmake-build-relwithdebinfo/benchmark/benchmarks/entt-more/ecs-benchmark-entt-more --benchmark_format=json > ./reports/entt-more.json
./cmake-build-relwithdebinfo/benchmark/benchmarks/entityx-more/ecs-benchmark-entityx-more --benchmark_format=json > ./reports/entityx-more.json
./cmake-build-relwithdebinfo/benchmark/benchmarks/ginseng-more/ecs-benchmark-ginseng-more --benchmark_format=json > ./reports/ginseng-more.json
./cmake-build-relwithdebinfo/benchmark/benchmarks/mustache-more/ecs-benchmark-mustache-more --benchmark_format=json > ./reports/mustache-more.json
./cmake-build-relwithdebinfo/benchmark/benchmarks/openecs-more/ecs-benchmark-openecs-more --benchmark_format=json > ./reports/openecs-more.json
./cmake-build-relwithdebinfo/benchmark/benchmarks/flecs-more/ecs-benchmark-flecs-more --benchmark_format=json > ./reports/flecs-more.json


./cmake-build-relwithdebinfo/benchmark/benchmarks/oop/ecs-benchmark-oop --benchmark_format=json > ./reports/oop.json
./cmake-build-relwithdebinfo/benchmark/benchmarks/oop/ecs-benchmark-oop-more --benchmark_format=json > ./reports/oop-more.json
