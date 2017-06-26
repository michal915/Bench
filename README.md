## Some C++ performance measurments

# Building
```
$mkdir build && cd build && cmake .. && make
```

# Usage with perf: 
```
perf record -g ./executable
perf report -g 'graph,0.5,caller'
```
