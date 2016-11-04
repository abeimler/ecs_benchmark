
## Benchmark

I run the benchmark with `/usr/bin/time` for more measurement.
``%Uuser %Ssystem %Eelapsed CPU:%P  max.memory:%Mk``


### Environment

 - OS: Linux Ubuntu 16.04 LTS 64-Bit Version
 - CPU: Intel® Core™ i5 CPU 760 @ 2.80GHz × 2 
 - RAM: 4 GB




### Result


|                            | EntityX2 (INITIAL\_CAPACITY=2097152)  | EntityX |  Anax (DEFAULT\_ENTITY\_POOL\_SIZE=2097152) | Anax (DEFAULT\_ENTITY\_POOL\_SIZE=1000) | Artemis |
|----------------------------|--------------------------------------:|--------:|--------------------------------------------:|----------------------------------------:|--------:|
| Time per Operation (ns/op) | 26                                    | 195     | 521                                         | 581                                     | 37112   |



#### EntityX

```bash
$ /usr/bin/time -f 'real %e user %U sys %S   %E elapsed    CPU: %P  Max.Memory: %Mk' ./build/ecs_benchmark --bench entityx\s+.* 
entityx create destroy entity with components                   10000000         195 ns/op

entityx    25 entities component systems update                   500000        2251 ns/op
entityx    50 entities component systems update                   500000        4477 ns/op
entityx   100 entities component systems update                   200000        8783 ns/op
entityx   200 entities component systems update                   100000       17975 ns/op
entityx   400 entities component systems update                    50000       33795 ns/op
entityx   800 entities component systems update                    20000       71798 ns/op
entityx  1600 entities component systems update                    10000      140192 ns/op
entityx  3200 entities component systems update                     5000      333915 ns/op
entityx  5000 entities component systems update                     2000      520089 ns/op
entityx 10000 entities component systems update                     1000     1019024 ns/op       1 ms/op
entityx 30000 entities component systems update                      500     2927072 ns/op       2 ms/op
entityx 100000 entities component systems update                     200    10449532 ns/op      10 ms/op  0.01 s/op
entityx 500000 entities component systems update                      50    51018049 ns/op      51 ms/op  0.05 s/op
entityx 1M entities component systems update                          10   106895076 ns/op     106 ms/op  0.11 s/op
entityx 2M entities component systems update                           5   246382913 ns/op     246 ms/op  0.25 s/op

./build/ecs_benchmark 47.901s
real 47.90 user 46.50 sys 0.53   0:47.90 elapsed    CPU: 98%  Max.Memory: 168772k



$ /usr/bin/time -f 'real %e user %U sys %S   %E elapsed    CPU: %P  Max.Memory: %Mk' ./build/ecs_benchmark --bench entityx2.* 
entityx2 create destroy entity with components                  50000000          26 ns/op

entityx2    25 entities component systems update                 2000000         504 ns/op
entityx2    50 entities component systems update                 2000000        1030 ns/op
entityx2   100 entities component systems update                  500000        2079 ns/op
entityx2   200 entities component systems update                  500000        3885 ns/op
entityx2   400 entities component systems update                  200000        8160 ns/op
entityx2   800 entities component systems update                  100000       15572 ns/op
entityx2  1600 entities component systems update                   50000       33412 ns/op
entityx2  3200 entities component systems update                   20000       65944 ns/op
entityx2  5000 entities component systems update                   20000      100512 ns/op
entityx2 10000 entities component systems update                    5000      211202 ns/op
entityx2 30000 entities component systems update                    2000      608559 ns/op
entityx2 100000 entities component systems update                    500     2396486 ns/op       2 ms/op
entityx2 500000 entities component systems update                    100    12699592 ns/op      12 ms/op  0.01 s/op
entityx2 1M entities component systems update                         50    25765807 ns/op      25 ms/op  0.03 s/op
entityx2 2M entities component systems update                         50    49633527 ns/op      49 ms/op  0.05 s/op

./build/ecs_benchmark 45.28s
real 45.28 user 44.08 sys 0.56   0:45.28 elapsed    CPU: 98%  Max.Memory: 171620k
```

In EntityX (compile-time) the Entity Capacity is set to `16777216`, to avoid bad_alloc exception.




#### Anax

```bash
$ /usr/bin/time -f 'real %e user %U sys %S   %E elapsed    CPU: %P  Max.Memory: %Mk' ./build/ecs_benchmark --bench anax.* 
anax create destroy entity with components                       1000000        1113 ns/op

anax    25 entities component systems update                     2000000         640 ns/op
anax    50 entities component systems update                     1000000        1176 ns/op
anax   100 entities component systems update                      500000        2084 ns/op
anax   200 entities component systems update                      500000        4319 ns/op
anax   400 entities component systems update                      200000        8848 ns/op
anax   800 entities component systems update                       50000       20849 ns/op
anax  1600 entities component systems update                       20000       60697 ns/op
anax  3200 entities component systems update                       10000      138414 ns/op
anax  5000 entities component systems update                        5000      210032 ns/op
anax 10000 entities component systems update                        5000      416882 ns/op
anax 30000 entities component systems update                         500     2336594 ns/op       2 ms/op
anax 100000 entities component systems update                        100    11561106 ns/op      11 ms/op  0.01 s/op
anax 500000 entities component systems update                         20    70372490 ns/op      70 ms/op  0.07 s/op
anax 1M entities component systems update                              5   233405829 ns/op     233 ms/op  0.23 s/op
anax 2M entities component systems update                              1  1381930888 ns/op    1381 ms/op  1.38 s/op

./build/ecs_benchmark 44.219s
real 44.22 user 41.26 sys 2.88   0:44.22 elapsed    CPU: 99%  Max.Memory: 1519212k
```



#### Artemis

```bash
$ /usr/bin/time -f 'real %e user %U sys %S   %E elapsed    CPU: %P  Max.Memory: %Mk' ./build/ecs_benchmark --bench artemis.* 
artemis create destroy entity with components                     100000         37112 ns/op

artemis    25 entities component systems update                   500000          2733 ns/op
artemis    50 entities component systems update                   200000          5392 ns/op
artemis   100 entities component systems update                   100000         11554 ns/op
artemis   200 entities component systems update                    50000         23692 ns/op
artemis   400 entities component systems update                    50000         47759 ns/op
artemis   800 entities component systems update                    20000         96441 ns/op
artemis  1600 entities component systems update                    10000        186906 ns/op
artemis  3200 entities component systems update                     5000        383143 ns/op
artemis  5000 entities component systems update                     2000        600745 ns/op
artemis 10000 entities component systems update                     1000       1099779 ns/op        1 ms/op
artemis 30000 entities component systems update                      500       3882497 ns/op        3 ms/op
artemis 100000 entities component systems update                       1    2154972063 ns/op     2154 ms/op    2.15 s/op
artemis 500000 entities component systems update                       1   53953525222 ns/op    53953 ms/op   53.95 s/op
artemis 1M entities component systems update                           1  222706059090 ns/op   222706 ms/op  222.71 s/op
artemis 2M entities component systems update                           1 1084524141193 ns/op  1084524 ms/op 1084.52 s/op

./build/ecs_benchmark 1402.68s
real 1402.67 user 1392.20 sys 2.94   23:22.67 elapsed    CPU: 99%  Max.Memory: 509292k
```



