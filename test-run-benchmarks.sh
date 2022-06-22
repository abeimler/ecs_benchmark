#!/usr/bin/env bash

#./build.sh

./cmake-build-relwithdebinfo/benchmark/benchmarks/entt-entities/ecs-benchmark-entt-entities --benchmark_format=json > ./reports/entt-entities.json
./cmake-build-relwithdebinfo/benchmark/benchmarks/entt/ecs-benchmark-entt --benchmark_format=json > ./reports/entt.json
./cmake-build-relwithdebinfo/benchmark/benchmarks/entt-extended/ecs-benchmark-entt-extended --benchmark_format=json > ./reports/entt-extended.json
sleep 1
./cmake-build-relwithdebinfo/benchmark/benchmarks/entt-extended/ecs-benchmark-entt-extended-runtime --benchmark_format=json > ./reports/entt-extended-runtime.json
./cmake-build-relwithdebinfo/benchmark/benchmarks/entt-extended/ecs-benchmark-entt-extended-stable --benchmark_format=json > ./reports/entt-extended-stable.json
./cmake-build-relwithdebinfo/benchmark/benchmarks/entt-extended/ecs-benchmark-entt-extended-group --benchmark_format=json > ./reports/entt-extended-group.json
sleep 1
./cmake-build-relwithdebinfo/benchmark/benchmarks/entt-extended/ecs-benchmark-entt-extended-non-owning-group --benchmark_format=json > ./reports/entt-extended-non-owning-group.json
./cmake-build-relwithdebinfo/benchmark/benchmarks/entt-extended/ecs-benchmark-entt-extended-full-owning-group --benchmark_format=json > ./reports/entt-extended-full-owning-group.json
./cmake-build-relwithdebinfo/benchmark/benchmarks/entt-extended/ecs-benchmark-entt-extended-partial-owning-group --benchmark_format=json > ./reports/entt-extended-partial-owning-group.json
sleep 1

./cmake-build-relwithdebinfo/benchmark/benchmarks/entityx-entities/ecs-benchmark-entityx-entities --benchmark_format=json > ./reports/entityx-entities.json
./cmake-build-relwithdebinfo/benchmark/benchmarks/entityx/ecs-benchmark-entityx --benchmark_format=json > ./reports/entityx.json
./cmake-build-relwithdebinfo/benchmark/benchmarks/entityx-extended/ecs-benchmark-entityx-extended --benchmark_format=json > ./reports/entityx-extended.json
sleep 1

./cmake-build-relwithdebinfo/benchmark/benchmarks/ginseng-entities/ecs-benchmark-ginseng-entities --benchmark_format=json > ./reports/ginseng-entities.json
./cmake-build-relwithdebinfo/benchmark/benchmarks/ginseng/ecs-benchmark-ginseng --benchmark_format=json > ./reports/ginseng.json
./cmake-build-relwithdebinfo/benchmark/benchmarks/ginseng-extended/ecs-benchmark-ginseng-extended --benchmark_format=json > ./reports/ginseng-extended.json
sleep 1

./cmake-build-relwithdebinfo/benchmark/benchmarks/mustache-entities/ecs-benchmark-mustache-entities --benchmark_format=json > ./reports/mustache-entities.json
./cmake-build-relwithdebinfo/benchmark/benchmarks/mustache/ecs-benchmark-mustache --benchmark_format=json > ./reports/mustache.json
./cmake-build-relwithdebinfo/benchmark/benchmarks/mustache-extended/ecs-benchmark-mustache-extended --benchmark_format=json > ./reports/mustache-extended.json
sleep 1

./cmake-build-relwithdebinfo/benchmark/benchmarks/openecs-entities/ecs-benchmark-openecs-entities --benchmark_format=json > ./reports/openecs-entities.json
./cmake-build-relwithdebinfo/benchmark/benchmarks/openecs/ecs-benchmark-openecs --benchmark_format=json > ./reports/openecs.json
./cmake-build-relwithdebinfo/benchmark/benchmarks/openecs-extended/ecs-benchmark-openecs-extended --benchmark_format=json > ./reports/openecs-extended.json
sleep 1

./cmake-build-relwithdebinfo/benchmark/benchmarks/flecs-entities/ecs-benchmark-flecs-entities --benchmark_format=json > ./reports/flecs-entities.json
./cmake-build-relwithdebinfo/benchmark/benchmarks/flecs/ecs-benchmark-flecs --benchmark_format=json > ./reports/flecs.json
./cmake-build-relwithdebinfo/benchmark/benchmarks/flecs-extended/ecs-benchmark-flecs-extended --benchmark_format=json > ./reports/flecs-extended.json
sleep 1


./cmake-build-relwithdebinfo/benchmark/benchmarks/oop/ecs-benchmark-oop --benchmark_format=json > ./reports/oop.json
sleep 1
./cmake-build-relwithdebinfo/benchmark/benchmarks/entt-extended/ecs-benchmark-entt-extended --benchmark_filter="Complex" --benchmark_format=json > ./reports/entt-complex.json
./cmake-build-relwithdebinfo/benchmark/benchmarks/entt-extended/ecs-benchmark-entt-extended-runtime --benchmark_filter="Complex" --benchmark_format=json > ./reports/entt-complex-runtime.json
./cmake-build-relwithdebinfo/benchmark/benchmarks/entt-extended/ecs-benchmark-entt-extended-stable --benchmark_filter="Complex" --benchmark_format=json > ./reports/entt-complex-stable.json
./cmake-build-relwithdebinfo/benchmark/benchmarks/entt-extended/ecs-benchmark-entt-extended-group --benchmark_filter="Complex" --benchmark_format=json > ./reports/entt-complex-group.json
./cmake-build-relwithdebinfo/benchmark/benchmarks/entityx-extended/ecs-benchmark-entityx-extended --benchmark_filter="Complex" --benchmark_format=json > ./reports/entityx-complex.json
./cmake-build-relwithdebinfo/benchmark/benchmarks/ginseng-extended/ecs-benchmark-ginseng-extended --benchmark_filter="Complex" --benchmark_format=json > ./reports/ginseng-complex.json
./cmake-build-relwithdebinfo/benchmark/benchmarks/mustache-extended/ecs-benchmark-mustache-extended --benchmark_filter="Complex" --benchmark_format=json > ./reports/mustache-complex.json
./cmake-build-relwithdebinfo/benchmark/benchmarks/openecs-extended/ecs-benchmark-openecs-extended --benchmark_filter="Complex" --benchmark_format=json > ./reports/openecs-complex.json
./cmake-build-relwithdebinfo/benchmark/benchmarks/flecs-extended/ecs-benchmark-flecs-extended --benchmark_filter="Complex" --benchmark_format=json > ./reports/flecs-complex.json
./cmake-build-relwithdebinfo/benchmark/benchmarks/oop/ecs-benchmark-oop-complex --benchmark_filter="Complex" --benchmark_format=json > ./reports/oop-complex.json
sleep 1

