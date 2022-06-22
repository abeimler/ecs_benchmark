#!/usr/bin/env bash

#./build.sh

./build/benchmark/benchmarks/entt-entities/ecs-benchmark-entt-entities --benchmark_format=json > ./reports/entt-entities.json
./build/benchmark/benchmarks/entt/ecs-benchmark-entt --benchmark_format=json > ./reports/entt.json
./build/benchmark/benchmarks/entt-extended/ecs-benchmark-entt-extended --benchmark_format=json > ./reports/entt-extended.json

./build/benchmark/benchmarks/entt-extended/ecs-benchmark-entt-extended-runtime --benchmark_format=json > ./reports/entt-extended-runtime.json
./build/benchmark/benchmarks/entt-extended/ecs-benchmark-entt-extended-stable --benchmark_format=json > ./reports/entt-extended-stable.json
./build/benchmark/benchmarks/entt-extended/ecs-benchmark-entt-extended-group --benchmark_format=json > ./reports/entt-extended-group.json

./build/benchmark/benchmarks/entt-extended/ecs-benchmark-entt-extended-non-owning-group --benchmark_format=json > ./reports/entt-extended-non-owning-group.json
./build/benchmark/benchmarks/entt-extended/ecs-benchmark-entt-extended-full-owning-group --benchmark_format=json > ./reports/entt-extended-full-owning-group.json
./build/benchmark/benchmarks/entt-extended/ecs-benchmark-entt-extended-partial-owning-group --benchmark_format=json > ./reports/entt-extended-partial-owning-group.json


./build/benchmark/benchmarks/entityx-entities/ecs-benchmark-entityx-entities --benchmark_format=json > ./reports/entityx-entities.json
./build/benchmark/benchmarks/entityx/ecs-benchmark-entityx --benchmark_format=json > ./reports/entityx.json
./build/benchmark/benchmarks/entityx-extended/ecs-benchmark-entityx-extended --benchmark_format=json > ./reports/entityx-extended.json


./build/benchmark/benchmarks/ginseng-entities/ecs-benchmark-ginseng-entities --benchmark_format=json > ./reports/ginseng-entities.json
./build/benchmark/benchmarks/ginseng/ecs-benchmark-ginseng --benchmark_format=json > ./reports/ginseng.json
./build/benchmark/benchmarks/ginseng-extended/ecs-benchmark-ginseng-extended --benchmark_format=json > ./reports/ginseng-extended.json


./build/benchmark/benchmarks/mustache-entities/ecs-benchmark-mustache-entities --benchmark_format=json > ./reports/mustache-entities.json
./build/benchmark/benchmarks/mustache/ecs-benchmark-mustache --benchmark_format=json > ./reports/mustache.json
./build/benchmark/benchmarks/mustache-extended/ecs-benchmark-mustache-extended --benchmark_format=json > ./reports/mustache-extended.json


./build/benchmark/benchmarks/openecs-entities/ecs-benchmark-openecs-entities --benchmark_format=json > ./reports/openecs-entities.json
./build/benchmark/benchmarks/openecs/ecs-benchmark-openecs --benchmark_format=json > ./reports/openecs.json
./build/benchmark/benchmarks/openecs-extended/ecs-benchmark-openecs-extended --benchmark_format=json > ./reports/openecs-extended.json


./build/benchmark/benchmarks/flecs-entities/ecs-benchmark-flecs-entities --benchmark_format=json > ./reports/flecs-entities.json
./build/benchmark/benchmarks/flecs/ecs-benchmark-flecs --benchmark_format=json > ./reports/flecs.json
./build/benchmark/benchmarks/flecs-extended/ecs-benchmark-flecs-extended --benchmark_format=json > ./reports/flecs-extended.json


./build/benchmark/benchmarks/oop/ecs-benchmark-oop --benchmark_format=json > ./reports/oop.json

./build/benchmark/benchmarks/entt-extended/ecs-benchmark-entt-extended --benchmark_filter="Complex" --benchmark_format=json > ./reports/entt-complex.json
./build/benchmark/benchmarks/entt-extended/ecs-benchmark-entt-extended-runtime --benchmark_filter="Complex" --benchmark_format=json > ./reports/entt-complex-runtime.json
./build/benchmark/benchmarks/entt-extended/ecs-benchmark-entt-extended-stable --benchmark_filter="Complex" --benchmark_format=json > ./reports/entt-complex-stable.json
./build/benchmark/benchmarks/entt-extended/ecs-benchmark-entt-extended-group --benchmark_filter="Complex" --benchmark_format=json > ./reports/entt-complex-group.json
./build/benchmark/benchmarks/entityx-extended/ecs-benchmark-entityx-extended --benchmark_filter="Complex" --benchmark_format=json > ./reports/entityx-complex.json
./build/benchmark/benchmarks/ginseng-extended/ecs-benchmark-ginseng-extended --benchmark_filter="Complex" --benchmark_format=json > ./reports/ginseng-complex.json
./build/benchmark/benchmarks/mustache-extended/ecs-benchmark-mustache-extended --benchmark_filter="Complex" --benchmark_format=json > ./reports/mustache-complex.json
./build/benchmark/benchmarks/openecs-extended/ecs-benchmark-openecs-extended --benchmark_filter="Complex" --benchmark_format=json > ./reports/openecs-complex.json
./build/benchmark/benchmarks/flecs-extended/ecs-benchmark-flecs-extended --benchmark_filter="Complex" --benchmark_format=json > ./reports/flecs-complex.json
./build/benchmark/benchmarks/oop/ecs-benchmark-oop-complex --benchmark_filter="Complex" --benchmark_format=json > ./reports/oop-complex.json


