# C++ performance measurments
[!Build Status](https://travis-ci.org/michal915/Bench.svg?branch=master)

## Building
```
$ mkdir build && cd build && cmake .. && make
```

## Usage with perf: 
```
$ perf record -g ./executable
$ perf report -g 'graph,0.5,caller'
```
