
# Old but meaningful Benchmarks

## Benchmark

I run the benchmark with `/usr/bin/time` for more measurement.


### Environment

 - OS: Linux Ubuntu 16.04 LTS 64-Bit Version
 - CPU: Intel® Core™ i7-3770K CPU @ 3.50GHz × 4 
 - RAM: 8 GB




### Result

#### EntityX

```bash
$ /usr/bin/time ./build/ecs_benchmark --bench entityx.*
entityx2 create destroy entity with components                 100000000              11 ns/op           0 ms/op

entityx2    25 entities component systems update                 5000000             253 ns/op           0 ms/op
entityx2    50 entities component systems update                 2000000             512 ns/op           0 ms/op
entityx2   100 entities component systems update                 1000000            1013 ns/op           0 ms/op
entityx2   200 entities component systems update                  500000            2028 ns/op           0 ms/op
entityx2   400 entities component systems update                  500000            4032 ns/op           0 ms/op
entityx2   800 entities component systems update                  200000            8045 ns/op           0 ms/op
entityx2  1600 entities component systems update                  100000           16295 ns/op           0 ms/op
entityx2  3200 entities component systems update                   50000           32925 ns/op           0 ms/op
entityx2  5000 entities component systems update                   20000           52012 ns/op           0 ms/op
entityx2 10000 entities component systems update                   10000          103898 ns/op           0 ms/op
entityx2 30000 entities component systems update                    5000          312005 ns/op           0 ms/op
entityx2 100000 entities component systems update                   1000         1138549 ns/op           1 ms/op
entityx2 500000 entities component systems update                    200         6822237 ns/op           6 ms/op
entityx2 1M entities component systems update                        100        13581160 ns/op          13 ms/op
entityx2 2M entities component systems update                         50        27446855 ns/op          27 ms/op


entityx create destroy entity with components                   10000000             158 ns/op           0 ms/op

entityx    25 entities component systems update                  1000000            1355 ns/op           0 ms/op
entityx    50 entities component systems update                   500000            2709 ns/op           0 ms/op
entityx   100 entities component systems update                   200000            5354 ns/op           0 ms/op
entityx   200 entities component systems update                   100000           10705 ns/op           0 ms/op
entityx   400 entities component systems update                    50000           21538 ns/op           0 ms/op
entityx   800 entities component systems update                    50000           42644 ns/op           0 ms/op
entityx  1600 entities component systems update                    20000           85357 ns/op           0 ms/op
entityx  3200 entities component systems update                    10000          176464 ns/op           0 ms/op
entityx  5000 entities component systems update                     5000          267848 ns/op           0 ms/op
entityx 10000 entities component systems update                     2000          549676 ns/op           0 ms/op
entityx 30000 entities component systems update                     1000         1716154 ns/op           1 ms/op
entityx 100000 entities component systems update                     200         5555625 ns/op           5 ms/op
entityx 500000 entities component systems update                      50        28519338 ns/op          28 ms/op
entityx 1M entities component systems update                          20        59526020 ns/op          59 ms/op
entityx 2M entities component systems update                          10       126546487 ns/op         126 ms/op

./build/ecs_benchmark 83.007s
82.41user 0.44system 1:23.00elapsed 99%CPU (0avgtext+0avgdata 172596maxresident)k
0inputs+0outputs (0major+287987minor)pagefaults 0swaps

```

In EntityX (compile-time) the Entity Capacity is set to `16777216`, to avoid bad_alloc exception.




#### Anax

```bash
$ /usr/bin/time ./build/ecs_benchmark --bench anax.*
anax create destroy entity with components                       2000000             581 ns/op           0 ms/op

anax    25 entities component systems update                     5000000             407 ns/op           0 ms/op
anax    50 entities component systems update                     2000000             719 ns/op           0 ms/op
anax   100 entities component systems update                     1000000            1351 ns/op           0 ms/op
anax   200 entities component systems update                      500000            2772 ns/op           0 ms/op
anax   400 entities component systems update                      200000            5515 ns/op           0 ms/op
anax   800 entities component systems update                      100000           12663 ns/op           0 ms/op
anax  1600 entities component systems update                       50000           28900 ns/op           0 ms/op
anax  3200 entities component systems update                       20000           65675 ns/op           0 ms/op
anax  5000 entities component systems update                       20000           98019 ns/op           0 ms/op
anax 10000 entities component systems update                        5000          207962 ns/op           0 ms/op
anax 30000 entities component systems update                        1000         1404356 ns/op           1 ms/op
anax 100000 entities component systems update                        200         7378245 ns/op           7 ms/op
anax 500000 entities component systems update                         50        41724988 ns/op          41 ms/op
anax 1M entities component systems update                             10       114361612 ns/op         114 ms/op
anax 2M entities component systems update                              5       304180312 ns/op         304 ms/op

./build/ecs_benchmark 48.004s
46.26user 1.68system 0:48.00elapsed 99%CPU (0avgtext+0avgdata 1523884maxresident)k
0inputs+0outputs (0major+281344minor)pagefaults 0swaps

```



#### Artemis

```bash
$ /usr/bin/time ./build/ecs_benchmark --bench artemis.*
artemis create destroy entity with components                     100000           27560 ns/op           0 ms/op

artemis    25 entities component systems update                  1000000            1850 ns/op           0 ms/op
artemis    50 entities component systems update                   500000            3739 ns/op           0 ms/op
artemis   100 entities component systems update                   200000            7171 ns/op           0 ms/op
artemis   200 entities component systems update                   100000           15105 ns/op           0 ms/op
artemis   400 entities component systems update                    50000           30838 ns/op           0 ms/op
artemis   800 entities component systems update                    20000           57808 ns/op           0 ms/op
artemis  1600 entities component systems update                    10000          118610 ns/op           0 ms/op
artemis  3200 entities component systems update                     5000          238977 ns/op           0 ms/op
artemis  5000 entities component systems update                     5000          370044 ns/op           0 ms/op
artemis 10000 entities component systems update                     2000          766931 ns/op           0 ms/op
artemis 30000 entities component systems update                      500         2637299 ns/op           2 ms/op
artemis 100000 entities component systems update                       1      1771098554 ns/op        1771 ms/op
artemis 500000 entities component systems update                       1     43347850038 ns/op       43347 ms/op
artemis 1M entities component systems update                           1    178245581448 ns/op      178245 ms/op
artemis 2M entities component systems update                           1    751284287440 ns/op      751284 ms/op

./build/ecs_benchmark 1010.9s
1010.21user 0.36system 16:50.89elapsed 99%CPU (0avgtext+0avgdata 509212maxresident)k
0inputs+0outputs (0major+167879minor)pagefaults 0swaps
```

Beware of the "2M entities"-benchmark, it can throw an bad_alloc exception.

