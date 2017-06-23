## Some C++ performance measurments

# Usage with perf: 
```
perf record -g ./executable
perf report -g 'graph,0.5,caller'
```
