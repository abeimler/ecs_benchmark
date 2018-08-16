#!/bin/bash

date
uname -a
printf "\n"
printf "\n"
printf "\n"

## use /usr/bin/time for more measurement
format="real %e user %U sys %S   %E elapsed    CPU: %P  Max.Memory: %Mk"
pformat="real %%e user %%U sys %%S   %%E elapsed    CPU: %%P  Max.Memory: %%Mk"



## run EntityX1 systems update benchmark
printf "$ /usr/bin/time -f '$pformat' ./build/ecs_benchmark --bench .*entityx1.*update.* \n"
/usr/bin/time -f "$format" ./build/ecs_benchmark --bench ".*entityx1.*update.*"
printf "\n"
printf "\n"

## run EntityX1 and Eventpp eventbus benchmarks
printf "$ /usr/bin/time -f '$pformat' ./build/ecs_benchmark --bench .*entityx-eventbus.* --bench .*eventpp-eventbus.* \n"
/usr/bin/time -f "$format" ./build/ecs_benchmark --bench ".*entityx-eventbus.*" --bench ".*eventpp-eventbus.*"
printf "\n"
printf "\n"


## run EntityX2 systems update benchmark
printf "$ /usr/bin/time -f '$pformat' ./build/ecs_benchmark --bench .*entityx2.*update.* \n"
/usr/bin/time -f "$format" ./build/ecs_benchmark --bench ".*entityx2.*update.*"
printf "\n"
printf "\n"


## run EnTT systems update benchmark
printf "$ /usr/bin/time -f '$pformat' ./build/ecs_benchmark --bench .*entt.*update.* \n"
/usr/bin/time -f "$format" ./build/ecs_benchmark --bench ".*entt.*update.*"
printf "\n"
printf "\n"

## run Ginseng systems update benchmark
printf "$ /usr/bin/time -f '$pformat' ./build/ecs_benchmark --bench .*ginseng.*update.* \n"
/usr/bin/time -f "$format" ./build/ecs_benchmark --bench ".*ginseng.*update.*"
printf "\n"
printf "\n"


## run Anax systems update benchmark
printf "$ /usr/bin/time -f '$pformat' ./build/ecs_benchmark --bench .*anax.*update.* \n"
/usr/bin/time -f "$format" ./build/ecs_benchmark --bench ".*anax.*update.*"
printf "\n"
printf "\n"



## run Artemis systems update benchmark
printf "$ /usr/bin/time -f '$pformat' ../build/ecs_benchmark --bench .*artemis.*update.* \n"
/usr/bin/time -f "$format" ./build/ecs_benchmark --bench ".*artemis.*update.*"
printf "\n"
printf "\n"

### use/see "EntityX1, EntityX2 and EnTT 10M entities benchmarks"
## run EntityX1, EntityX2 and EnTT create, destory benchmarks (exclude Anax, it causes bad_alloc)
#printf "$ /usr/bin/time -f '$pformat' ./build/ecs_benchmark --bench .*entityx1.*create.* --bench .*entityx2.*create.* --bench .*entt.*create.* \n"
#/usr/bin/time -f "$format" ./build/ecs_benchmark --bench ".*entityx1.*create.*" --bench ".*entityx2.*create.*" --bench ".*entt.*create.*"
#printf "\n"
#printf "\n"




## run EntityX1, EntityX2, EnTT, and Ginseng 10M entities benchmarks (exclude Anax, it causes bad_alloc)
printf "$ /usr/bin/time -f '$pformat' ./build/ecs_benchmark --bench .*entityx1.*10M\\s+entities.* --bench .*entityx2.*10M\\s+entities.* --bench .*entt.*10M\\s+entities.* --bench .*ginseng.*10M\\s+entities.* \n"
/usr/bin/time -f "$format" ./build/ecs_benchmark --bench ".*entityx1.*10M\\s+entities.*" --bench ".*entityx2.*10M\\s+entities.*" --bench ".*entt.*10M\\s+entities.*" --bench ".*ginseng.*10M\\s+entities.*"
printf "\n"
printf "\n"


./scripts/run_benchmark_plot_old.sh
