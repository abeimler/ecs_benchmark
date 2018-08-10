#!/bin/bash

## use /usr/bin/time for more measurement
format="real %e user %U sys %S   %E elapsed    CPU: %P  Max.Memory: %Mk"
pformat="real %%e user %%U sys %%S   %%E elapsed    CPU: %%P  Max.Memory: %%Mk"



## run EntityX1, EntityX2 and EnTT systems update benchmarks, write gnuplot data
printf "$ ./build/ecs_benchmark --bench .*entityx1.*update.* --bench .*entityx2.*update.* --bench .*entt.*update.* --plotdata --csvoutput=./doc/csv > ./doc/data-systems-update.dat \n"
./build/ecs_benchmark --bench ".*entityx1.*update.*" --bench ".*entityx2.*update.*"  --bench ".*entt.*update.*" --plotdata --csvoutput=./doc/csv > ./doc/data-systems-update.dat
printf "\n"

### skip artemis, if it takes to long
## run EntityX1, EntityX2 and EnTT systems update benchmarks, write gnuplot data
printf "$ ./build/ecs_benchmark --bench .*anax.*update.* --bench .*entityx1.*update.* --bench .*entityx2.*update.* --bench .*entt.*update.* --bench .*artemis.*update.* --plotdata --csvoutput=./doc/csv > ./doc/data-systems-update-2.dat \n"
./build/ecs_benchmark --bench ".*anax.*update.*" --bench ".*entityx1.*update.*" --bench ".*entityx2.*update.*"  --bench ".*entt.*update.*" --bench ".*artemis.*update.*" --plotdata --csvoutput=./doc/csv > ./doc/data-systems-update-2.dat
#printf "$ ./build/ecs_benchmark --bench .*anax.*update.* --bench .*entityx1.*update.* --bench .*entityx2.*update.* --bench .*entt.*update.* --plotdata --csvoutput=./doc/csv > ./doc/data-systems-update-2.dat \n"
#./build/ecs_benchmark --bench ".*anax.*update.*" --bench ".*entityx1.*update.*" --bench ".*entityx2.*update.*"  --bench ".*entt.*update.*" --plotdata --csvoutput=./doc/csv > ./doc/data-systems-update-2.dat
printf "\n"

## run EntityX1 and Eventpp eventbus benchmarks, write gnuplot data
printf "$ ./build/ecs_benchmark --bench .*entityx-eventbus.* --bench .*eventpp-eventbus.* --plotdata --csvoutput=./doc/csv > ./doc/data-eventbus.dat \n"
./build/ecs_benchmark --bench ".*entityx-eventbus.*" --bench ".*eventpp-eventbus.*" --plotdata --csvoutput=./doc/csv > ./doc/data-eventbus.dat
printf "\n"

## plot benchmark data
cd ./doc
gnuplot ../scripts/data-systems-update.plt
gnuplot ../scripts/data-systems-update-2.plt
gnuplot ../scripts/data-eventbus.plt