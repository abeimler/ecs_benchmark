#!/usr/bin/env bash

#./run-benchmarks.sh


python3 ./scripts/gen-benchmark-report -c ./plot.config.json gen-plots ./reports/entityx.json ./reports/entt.json ./reports/ginseng.json ./reports/mustache.json ./reports/flecs.json ./reports/openecs.json
python3 ./scripts/gen-benchmark-report -c ./plot.config.json gen-results-md ./reports/entityx.json ./reports/entt.json ./reports/ginseng.json ./reports/mustache.json ./reports/flecs.json ./reports/openecs.json

python3 ./scripts/gen-benchmark-report -c ./plot.config.json gen-plots ./reports/entityx-entities.json ./reports/entt-entities.json ./reports/ginseng-entities.json \
					  ./reports/mustache-entities.json ./reports/openecs-entities.json ./reports/flecs-entities.json
python3 ./scripts/gen-benchmark-report -c ./plot.config.json gen-results-md -o entities.RESULTS.md ./reports/entityx-entities.json ./reports/entt-entities.json \
					  ./reports/ginseng-entities.json ./reports/mustache-entities.json ./reports/openecs-entities.json ./reports/flecs-entities.json

python3 ./scripts/gen-benchmark-report -c ./plot.config.json gen-plots ./reports/entityx-extended.json ./reports/entt-extended.json ./reports/entt-extended-runtime.json \
                                                                                                       ./reports/entt-extended-group.json ./reports/entt-extended-full-owning-group.json \
                                                                                                       ./reports/entt-extended-non-owning-group.json ./reports/entt-extended-partial-owning-group.json \
                                                                                                       ./reports/entt-extended-stable.json ./reports/ginseng-extended.json ./reports/mustache-extended.json \
                                                                                                       ./reports/openecs-extended.json ./reports/flecs-extended.json ./reports/openecs-extended.json
                                                                                                       
python3 ./scripts/gen-benchmark-report -c ./plot.config.json gen-results-md -o extended.RESULTS.md ./reports/entityx-extended.json ./reports/entt-extended.json ./reports/entt-extended-runtime.json \
                                                                                                   ./reports/entt-extended-group.json ./reports/entt-extended-full-owning-group.json \
                                                                                                   ./reports/entt-extended-non-owning-group.json ./reports/entt-extended-partial-owning-group.json \
                                                                                                   ./reports/entt-extended-stable.json ./reports/ginseng-extended.json ./reports/mustache-extended.json \
                                                                                                   ./reports/openecs-extended.json ./reports/flecs-extended.json ./reports/openecs-extended.json


#python3 ./scripts/gen-benchmark-report -c ./plot.config.json gen-plots ./reports/entityx-complex.json ./reports/entt-complex.json ./reports/entt-complex-runtime.json ./reports/entt-complex-group.json \
#                                                                       ./reports/entt-complex-stable.json ./reports/ginseng-complex.json ./reports/mustache-complex.json ./reports/flecs-complex.json
#python3 ./scripts/gen-benchmark-report -c ./plot.config.json gen-results-md -o extended.oop.RESULTS.md ./reports/entityx-complex.json ./reports/entt-complex.json ./reports/entt-complex-runtime.json ./reports/entt-complex-group.json \
#                                                                       ./reports/entt-complex-stable.json ./reports/ginseng-complex.json ./reports/mustache-complex.json ./reports/flecs-complex.json
#                                                                       ./reports/oop-complex.json
