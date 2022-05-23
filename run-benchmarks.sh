#!/usr/bin/env bash

./build.sh

./build/benchmark/benchmarks/openecs/ecs-benchmark-entt --benchmark_format=json > ./reports/entt.json