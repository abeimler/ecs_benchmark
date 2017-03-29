#!/bin/bash

date
uname -a

format="real %e user %U sys %S   %E elapsed    CPU: %P  Max.Memory: %Mk"
pformat="real %%e user %%U sys %%S   %%E elapsed    CPU: %%P  Max.Memory: %%Mk"

printf "$ /usr/bin/time -f '$pformat' ../build/ecs_benchmark --bench .*entityx1.*update.* \n"
/usr/bin/time -f "$format" ../build/ecs_benchmark --bench ".*entityx1.*update.*"
printf "\n"
printf "\n"

printf "$ /usr/bin/time -f '$pformat' ../build/ecs_benchmark --bench .*entityx-eventbus.* --bench .*eventpp-eventbus.* \n"
/usr/bin/time -f "$format" ../build/ecs_benchmark --bench ".*entityx-eventbus.*" --bench ".*eventpp-eventbus.*"
printf "\n"
printf "\n"


printf "$ /usr/bin/time -f '$pformat' ../build/ecs_benchmark --bench .*entityx2.*update.* \n"
/usr/bin/time -f "$format" ../build/ecs_benchmark --bench ".*entityx2.*update.*"
printf "\n"
printf "\n"

printf "$ /usr/bin/time -f '$pformat' ../build/ecs_benchmark --bench .*entityx1.*create.* --bench .*entityx2.*create.* \n"
/usr/bin/time -f "$format" ../build/ecs_benchmark --bench ".*entityx1.*create.*" --bench ".*entityx2.*create.*"
printf "\n"
printf "\n"


printf "$ /usr/bin/time -f '$pformat' ../build/ecs_benchmark --bench .*anax.*update.* \n"
/usr/bin/time -f "$format" ../build/ecs_benchmark --bench ".*anax.*update.*"
printf "\n"
printf "\n"


### disable artemis, it takes to long
#printf "$ /usr/bin/time -f '$pformat' ../build/ecs_benchmark --bench .*artemis.*update.* \n"
#/usr/bin/time -f "$format" ../build/ecs_benchmark --bench ".*artemis.*update.*"
#printf "\n"
#printf "\n"

## with artemis.
#printf "$ ../build/ecs_benchmark --bench .*entityx1.*update.* --bench .*entityx2.*update.* --bench .*anax.*update.* --bench .*artemis.*update.* --plotdata > data.txt \n"
#../build/ecs_benchmark --bench ".*entityx1.*update.*" --bench ".*entityx2.*update.*" --bench ".*anax.*" --bench ".*artemis.*update.*" --plotdata > data.txt
#printf "\n"


printf "$ ../build/ecs_benchmark --bench .*entityx1.*update.* --bench .*entityx2.*update.* --bench .*anax.*update.* --plotdata > data-systems-update.txt \n"
../build/ecs_benchmark --bench ".*entityx1.*update.*" --bench ".*entityx2.*update.*" --bench ".*anax.*update.*" --plotdata > data-systems-update.txt
printf "\n"

printf "$ ../build/ecs_benchmark --bench .*entityx-eventbus.* --bench .*eventpp-eventbus.* --plotdata > data-eventbus.txt \n"
../build/ecs_benchmark --bench ".*entityx-eventbus.*" --bench ".*eventpp-eventbus.*" --plotdata > data-eventbus.txt
printf "\n"