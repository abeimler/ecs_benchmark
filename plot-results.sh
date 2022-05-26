#!/usr/bin/env bash

#./run-benchmarks.sh


python3 ./scripts/gen-benchmark-report -i ./info.json gen-plots ./reports/entityx.json ./reports/entt.json ./reports/ginseng.json ./reports/mustache.json ./reports/oop.json ./reports/openecs.json
python3 ./scripts/gen-benchmark-report -i ./info.json gen-plots ./reports/entityx-more.json ./reports/entt-more.json ./reports/ginseng-more.json ./reports/mustache-more.json ./reports/oop-more.json ./reports/openecs-more.json

python3 ./scripts/gen-benchmark-report -i ./info.json gen-results-md ./reports/entityx.json ./reports/entt.json ./reports/ginseng.json ./reports/mustache.json ./reports/oop.json ./reports/openecs.json

