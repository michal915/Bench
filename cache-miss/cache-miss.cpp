#include <iostream>
#include "benchmark/benchmark.h"

namespace Memory
{
  void end(void* p){asm volatile("" : : "g"(p) : "memory");}
  void read(){asm volatile("" : : : "memory");}
}


template<std::size_t row, std::size_t col>
static void ColMajor(benchmark::State& state)
{
  auto A = new int[row][col];
  int sum = 0;

  while (state.KeepRunning())
  {
    for(std::size_t c = 0; c < col; c++) {
      for(std::size_t r = 0; r < row; r++) {
        sum += A[r][c];
      }
    }
    Memory::end(&sum);
  }

  delete[] A;
}

template<std::size_t row, std::size_t col>
static void RowMajor(benchmark::State& state)
{
  auto A = new int[row][col];
  int sum = 0;

  while (state.KeepRunning())
  {
    for(std::size_t r = 0; r < row; r++) {
      for(std::size_t c = 0; c < col; c++) {
        sum += A[r][c];
      }
    }
    Memory::end(&sum);
  }
  delete[] A;
}

BENCHMARK_TEMPLATE(RowMajor,  100,  100);
BENCHMARK_TEMPLATE(ColMajor,  100,  100);
BENCHMARK_TEMPLATE(RowMajor, 1500, 1500);
BENCHMARK_TEMPLATE(ColMajor, 1500, 1500);
BENCHMARK_TEMPLATE(RowMajor, 3000, 3000);
BENCHMARK_TEMPLATE(ColMajor, 3000, 3000);
BENCHMARK_TEMPLATE(RowMajor, 5000, 5000);
BENCHMARK_TEMPLATE(ColMajor, 5000, 5000);

BENCHMARK_MAIN()
