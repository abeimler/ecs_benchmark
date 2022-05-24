#!/usr/bin/env bash

#./build.sh

./build/benchmark/benchmarks/entt/ecs-benchmark-entt --benchmark_format=json > ./reports/entt.json
./build/benchmark/benchmarks/entityx/ecs-benchmark-entityx --benchmark_format=json > ./reports/entityx.json
./build/benchmark/benchmarks/ginseng/ecs-benchmark-ginseng --benchmark_format=json > ./reports/ginseng.json
./build/benchmark/benchmarks/mustache/ecs-benchmark-mustache --benchmark_format=json > ./reports/mustache.json
./build/benchmark/benchmarks/openecs/ecs-benchmark-openecs --benchmark_format=json > ./reports/openecs.json
./build/benchmark/benchmarks/oop/ecs-benchmark-oop --benchmark_format=json > ./reports/oop.json