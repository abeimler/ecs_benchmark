#!/usr/bin/env bash


./out/build/windows-msvc-release-user-mode/benchmark/benchmarks/entt-entities/ecs-benchmark-entt-entities --benchmark_format=json > ./reports/entt-entities.json
./out/build/windows-msvc-release-user-mode/benchmark/benchmarks/entt/ecs-benchmark-entt --benchmark_format=json > ./reports/entt.json
./out/build/windows-msvc-release-user-mode/benchmark/benchmarks/entt-extended/ecs-benchmark-entt-extended --benchmark_format=json > ./reports/entt-extended.json

./out/build/windows-msvc-release-user-mode/benchmark/benchmarks/entt-extended/ecs-benchmark-entt-extended-runtime --benchmark_format=json > ./reports/entt-extended-runtime.json
./out/build/windows-msvc-release-user-mode/benchmark/benchmarks/entt-extended/ecs-benchmark-entt-extended-stable --benchmark_format=json > ./reports/entt-extended-stable.json
./out/build/windows-msvc-release-user-mode/benchmark/benchmarks/entt-extended/ecs-benchmark-entt-extended-group --benchmark_format=json > ./reports/entt-extended-group.json

./out/build/windows-msvc-release-user-mode/benchmark/benchmarks/entt-extended/ecs-benchmark-entt-extended-non-owning-group --benchmark_format=json > ./reports/entt-extended-non-owning-group.json
./out/build/windows-msvc-release-user-mode/benchmark/benchmarks/entt-extended/ecs-benchmark-entt-extended-full-owning-group --benchmark_format=json > ./reports/entt-extended-full-owning-group.json
./out/build/windows-msvc-release-user-mode/benchmark/benchmarks/entt-extended/ecs-benchmark-entt-extended-partial-owning-group --benchmark_format=json > ./reports/entt-extended-partial-owning-group.json


./out/build/windows-msvc-release-user-mode/benchmark/benchmarks/entityx-entities/ecs-benchmark-entityx-entities --benchmark_format=json > ./reports/entityx-entities.json
./out/build/windows-msvc-release-user-mode/benchmark/benchmarks/entityx/ecs-benchmark-entityx --benchmark_format=json > ./reports/entityx.json
./out/build/windows-msvc-release-user-mode/benchmark/benchmarks/entityx-extended/ecs-benchmark-entityx-extended --benchmark_format=json > ./reports/entityx-extended.json


./out/build/windows-msvc-release-user-mode/benchmark/benchmarks/ginseng-entities/ecs-benchmark-ginseng-entities --benchmark_format=json > ./reports/ginseng-entities.json
./out/build/windows-msvc-release-user-mode/benchmark/benchmarks/ginseng/ecs-benchmark-ginseng --benchmark_format=json > ./reports/ginseng.json
./out/build/windows-msvc-release-user-mode/benchmark/benchmarks/ginseng-extended/ecs-benchmark-ginseng-extended --benchmark_format=json > ./reports/ginseng-extended.json


./out/build/windows-msvc-release-user-mode/benchmark/benchmarks/mustache-entities/ecs-benchmark-mustache-entities --benchmark_format=json > ./reports/mustache-entities.json
./out/build/windows-msvc-release-user-mode/benchmark/benchmarks/mustache/ecs-benchmark-mustache --benchmark_format=json > ./reports/mustache.json
./out/build/windows-msvc-release-user-mode/benchmark/benchmarks/mustache-extended/ecs-benchmark-mustache-extended --benchmark_format=json > ./reports/mustache-extended.json


./out/build/windows-msvc-release-user-mode/benchmark/benchmarks/openecs-entities/ecs-benchmark-openecs-entities --benchmark_format=json > ./reports/openecs-entities.json
./out/build/windows-msvc-release-user-mode/benchmark/benchmarks/openecs/ecs-benchmark-openecs --benchmark_format=json > ./reports/openecs.json
./out/build/windows-msvc-release-user-mode/benchmark/benchmarks/openecs-extended/ecs-benchmark-openecs-extended --benchmark_format=json > ./reports/openecs-extended.json


./out/build/windows-msvc-release-user-mode/benchmark/benchmarks/flecs-entities/ecs-benchmark-flecs-entities --benchmark_format=json > ./reports/flecs-entities.json
./out/build/windows-msvc-release-user-mode/benchmark/benchmarks/flecs/ecs-benchmark-flecs --benchmark_format=json > ./reports/flecs.json
./out/build/windows-msvc-release-user-mode/benchmark/benchmarks/flecs-extended/ecs-benchmark-flecs-extended --benchmark_format=json > ./reports/flecs-extended.json


./out/build/windows-msvc-release-user-mode/benchmark/benchmarks/oop/ecs-benchmark-oop --benchmark_format=json > ./reports/oop.json

./out/build/windows-msvc-release-user-mode/benchmark/benchmarks/entt-extended/ecs-benchmark-entt-extended --benchmark_filter="Complex" --benchmark_format=json > ./reports/entt-complex.json
./out/build/windows-msvc-release-user-mode/benchmark/benchmarks/entt-extended/ecs-benchmark-entt-extended-runtime --benchmark_filter="Complex" --benchmark_format=json > ./reports/entt-complex-runtime.json
./out/build/windows-msvc-release-user-mode/benchmark/benchmarks/entt-extended/ecs-benchmark-entt-extended-stable --benchmark_filter="Complex" --benchmark_format=json > ./reports/entt-complex-stable.json
./out/build/windows-msvc-release-user-mode/benchmark/benchmarks/entt-extended/ecs-benchmark-entt-extended-group --benchmark_filter="Complex" --benchmark_format=json > ./reports/entt-complex-group.json
./out/build/windows-msvc-release-user-mode/benchmark/benchmarks/entityx-extended/ecs-benchmark-entityx-extended --benchmark_filter="Complex" --benchmark_format=json > ./reports/entityx-complex.json
./out/build/windows-msvc-release-user-mode/benchmark/benchmarks/ginseng-extended/ecs-benchmark-ginseng-extended --benchmark_filter="Complex" --benchmark_format=json > ./reports/ginseng-complex.json
./out/build/windows-msvc-release-user-mode/benchmark/benchmarks/mustache-extended/ecs-benchmark-mustache-extended --benchmark_filter="Complex" --benchmark_format=json > ./reports/mustache-complex.json
./out/build/windows-msvc-release-user-mode/benchmark/benchmarks/openecs-extended/ecs-benchmark-openecs-extended --benchmark_filter="Complex" --benchmark_format=json > ./reports/openecs-complex.json
./out/build/windows-msvc-release-user-mode/benchmark/benchmarks/flecs-extended/ecs-benchmark-flecs-extended --benchmark_filter="Complex" --benchmark_format=json > ./reports/flecs-complex.json
./out/build/windows-msvc-release-user-mode/benchmark/benchmarks/oop/ecs-benchmark-oop-complex --benchmark_filter="Complex" --benchmark_format=json > ./reports/oop-complex.json



