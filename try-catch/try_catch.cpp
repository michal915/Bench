#include <string>
#include <vector>
#include <benchmark/benchmark.h>
#include <memory>
#include <iostream>

namespace Memory
{
  void end(void* p) { asm volatile("" : : "g"(p) : "memory"); }
  void read() { asm volatile("" : : : "memory"); }
}

constexpr auto blockSize = 100000000ul;

static void if_else(benchmark::State& state) {

  while (state.KeepRunning()) 
  {  
    auto p = new (std::nothrow) int[blockSize];
       
    if (p == nullptr) 
    {
      Memory::read();
      throw; 
    }

    else
    {
      Memory::end(&p);
    }
    delete[] p;
  }
} 

static void try_catch(benchmark::State& state) 
{
  while (state.KeepRunning()) 
  {  
    try 
    {
      auto p = new int[blockSize];
      Memory::end(&p);
      delete[] p;
    } 
    
    catch (...) 
    {
      throw;
    }
  }
}


static void if_else_err(benchmark::State& state) 
{
  while (state.KeepRunning()) 
  {  
    while (true) 
    {
      auto p = new (std::nothrow) int[blockSize];

      if (p == nullptr)  
      {
        throw;
      }
       
      Memory::end(&p);
    }
  }
} 

static void try_catch_err(benchmark::State& state) 
{
  while (state.KeepRunning()) 
  {  
    while (true) 
    {
      try 
      {
        auto p = new int[blockSize];
        Memory::end(&p);
      } 
      
      catch (...) 
      {
        break;
      }
    }
  }
}

BENCHMARK(if_else);
BENCHMARK(try_catch);

//BENCHMARK(if_else_err);
//BENCHMARK(try_catch_err);

BENCHMARK_MAIN()
