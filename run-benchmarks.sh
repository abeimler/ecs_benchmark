#!/usr/bin/env bash

#./build.sh

./build/benchmark/benchmarks/entt/ecs-benchmark-entt --benchmark_format=json > ./reports/entt.json
./build/benchmark/benchmarks/entityx/ecs-benchmark-entityx --benchmark_format=json > ./reports/entityx.json
./build/benchmark/benchmarks/ginseng/ecs-benchmark-ginseng --benchmark_format=json > ./reports/ginseng.json
./build/benchmark/benchmarks/mustache/ecs-benchmark-mustache --benchmark_format=json > ./reports/mustache.json
./build/benchmark/benchmarks/openecs/ecs-benchmark-openecs --benchmark_format=json > ./reports/openecs.json
./build/benchmark/benchmarks/flecs/ecs-benchmark-flecs --benchmark_format=json > ./reports/flecs.json

./build/benchmark/benchmarks/entt-more/ecs-benchmark-entt-more --benchmark_format=json > ./reports/entt-more.json
./build/benchmark/benchmarks/entityx-more/ecs-benchmark-entityx-more --benchmark_format=json > ./reports/entityx-more.json
./build/benchmark/benchmarks/ginseng-more/ecs-benchmark-ginseng-more --benchmark_format=json > ./reports/ginseng-more.json
./build/benchmark/benchmarks/mustache-more/ecs-benchmark-mustache-more --benchmark_format=json > ./reports/mustache-more.json
./build/benchmark/benchmarks/openecs-more/ecs-benchmark-openecs-more --benchmark_format=json > ./reports/openecs-more.json
./build/benchmark/benchmarks/flecs-more/ecs-benchmark-flecs-more --benchmark_format=json > ./reports/flecs-more.json


./build/benchmark/benchmarks/oop/ecs-benchmark-oop-more --benchmark_format=json > ./reports/oop-more.json
#./build/benchmark/benchmarks/oop/ecs-benchmark-oop --benchmark_format=json > ./reports/oop.json


