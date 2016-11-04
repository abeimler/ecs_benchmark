#!/bin/bash

format="real %e user %U sys %S   %E elapsed    CPU: %P  Max.Memory: %Mk"
pformat="real %%e user %%U sys %%S   %%E elapsed    CPU: %%P  Max.Memory: %%Mk"

printf "$ /usr/bin/time -f '$pformat' ./build/ecs_benchmark --bench entityx\\s+.* \n"
/usr/bin/time -f "$format" ./build/ecs_benchmark --bench "entityx\\s+.*"
printf "\n"

printf "$ /usr/bin/time -f '$pformat' ./build/ecs_benchmark --bench entityx2.* \n"
/usr/bin/time -f "$format" ./build/ecs_benchmark --bench entityx2.*
printf "\n"


printf "$ /usr/bin/time -f '$pformat' ./build/ecs_benchmark --bench anax.* \n"
/usr/bin/time -f "$format" ./build/ecs_benchmark --bench anax.*
printf "\n"


printf "$ /usr/bin/time -f '$pformat' ./build/ecs_benchmark --bench artemis.* \n"
/usr/bin/time -f "$format" ./build/ecs_benchmark --bench artemis.*
printf "\n"
