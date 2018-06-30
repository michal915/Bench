#include <benchmark/benchmark.h>
#include <iostream>

namespace Memory
{
  void end(void* p) { asm volatile("" : : "g"(p) : "memory"); }
  void read() { asm volatile("" : : : "memory"); }
}

class ClearStream
{
public:

  ClearStream()
  {
    std::cout.setstate(std::ios::failbit);
  }

  ~ClearStream()
  {
    std::cout.clear();
  }
};

static void endl(benchmark::State& state)
{
  ClearStream cs {};
  while(state.KeepRunning())
  {
    std::cout << std::endl;
  }
}

static void _n(benchmark::State& state)
{
  ClearStream cs {};
  while(state.KeepRunning())
  {
    std::cout << "\n";
  }
}

static void _n_r(benchmark::State& state)
{
  ClearStream cs {};
  while(state.KeepRunning())
  {
    std::cout << "\n\r";
  }
}

BENCHMARK(endl);
BENCHMARK(_n);
BENCHMARK(_n_r);



BENCHMARK_MAIN();
