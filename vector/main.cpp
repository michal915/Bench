#include <benchmark/benchmark.h>
#include <string>
#include <vector>
const int i=5;
class Test {
  std::string mTitle;
  float mX, mY, mZ;

public:
  Test(std::string title, float x, float y, float z)
    : mTitle{std::move(title)}, mX(x), mY(y), mZ(z) 
  {}

  Test(const Test& t) 
    : mTitle(t.mTitle), mX(t.mX), mY(t.mY), mZ(t.mZ)
  {}

  Test(Test&& t) 
    : mTitle{std::move(t.mTitle)}, mX(t.mX), mY(t.mY), mZ(t.mZ) 
  {}

  ~Test()
  {
    mX = 0; mY = 0; mZ = 0;
    mTitle = "";
  }
};

namespace Memory
{
  void end(void* p)
  {
    asm volatile("" : : "g"(p) : "memory");
  }

  void read()
  {
    asm volatile("" : : : "memory");
  }
};

static void create(benchmark::State& state) {

  while(state.KeepRunning())
  {
    std::vector<Test> v;
    Memory::end(&v);
    (void)v;
  }
} 

static void reserve(benchmark::State& state) {
  while(state.KeepRunning())
  {
    std::vector<Test> v;
    v.reserve(1);
    Memory::end(v.data());
  }
}

static void push_back(benchmark::State& state) {
  while (state.KeepRunning())
  {
    std::vector<Test> v;
    Memory::end(&v);
    
    v.push_back(Test("test", i, i*10.0f, i*100.0f));
    Memory::read();
  }
}

static void push_back_reserve(benchmark::State& state) {
  while (state.KeepRunning())
  {
    std::vector<Test> v;
    v.reserve(1);
    Memory::end(v.data());
    
    v.push_back(Test("test", i, i*10.0f, i*100.0f));
    Memory::read();
  }
}


static void emplace_back_reserve(benchmark::State& state) {
  while (state.KeepRunning())
  {
    std::vector<Test> v;
    v.reserve(1);
    Memory::end(v.data());
    
    v.emplace_back("test", i, i*10.0f, i*100.0f);
    Memory::read();
  }
}

static void emplace_back(benchmark::State& state) {
  while (state.KeepRunning())
  {
    std::vector<Test> v;
    Memory::end(&v);
    
    v.emplace_back("test", i, i*10.0f, i*100.0f);
    Memory::read();
  }
}

BENCHMARK(push_back);
BENCHMARK(push_back_reserve);
BENCHMARK(emplace_back);
BENCHMARK(emplace_back_reserve);
BENCHMARK(create);
BENCHMARK(reserve);

BENCHMARK_MAIN();
