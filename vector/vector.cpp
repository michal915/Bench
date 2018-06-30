#include <benchmark/benchmark.h>
#include <string>
#include <vector>

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

constexpr std::size_t getN()
{
  return 100;
}

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
}

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

    v.push_back(Test("test", 1.0f, 10.0f, 100.0f));
    Memory::read();
  }
}

static void push_back_reserve(benchmark::State& state) {
  while (state.KeepRunning())
  {
    std::vector<Test> v;
    v.reserve(1);
    Memory::end(v.data());

    v.push_back(Test("test", 1.0f, 10.0f, 100.0f));
    Memory::read();
  }
}


static void emplace_back_reserve(benchmark::State& state) {
  while (state.KeepRunning())
  {
    std::vector<Test> v;
    v.reserve(1);
    Memory::end(v.data());

    v.emplace_back("test", 1.0f, 10.0f, 100.0f);
    Memory::read();
  }
}

static void emplace_back(benchmark::State& state) {
  while (state.KeepRunning())
  {
    std::vector<Test> v;
    Memory::end(&v);

    v.emplace_back("test", 1.0f, 10.0f, 100.0f);
    Memory::read();
  }
}

static void reserveN(benchmark::State& state) {
  while(state.KeepRunning())
  {
    std::vector<Test> v;
    v.reserve(getN());
    Memory::end(v.data());
  }
}

static void push_backN(benchmark::State& state) {
  while (state.KeepRunning())
  {
    std::vector<Test> v;
    Memory::end(&v);

    for(decltype(getN())i=0; i<getN(); i++)
    {
      v.push_back(Test("test", i*1.0f, i*10.0f, i*100.0f));
    }
    Memory::read();
  }
}

static void push_back_reserveN(benchmark::State& state) {
  while (state.KeepRunning())
  {
    std::vector<Test> v;
    v.reserve(1);
    Memory::end(v.data());

    for(decltype(getN())i=0; i<getN(); i++)
    {
      v.push_back(Test("test", i*1.0f, i*10.0f, i*100.0f));
    }
    Memory::read();
  }
}


static void emplace_back_reserveN(benchmark::State& state) {
  while (state.KeepRunning())
  {
    std::vector<Test> v;
    v.reserve(getN());
    Memory::end(v.data());

    for(decltype(getN())i=0; i<getN(); i++)
    {
      v.emplace_back("test", i*1.0f, i*10.0f, i*100.0f);
    }
    Memory::read();
  }
}

static void emplace_backN(benchmark::State& state) {
  while (state.KeepRunning())
  {
    std::vector<Test> v;
    Memory::end(&v);

    for(decltype(getN())i=0; i<getN(); i++)
    {
      v.emplace_back("test", i*1.0f, i*10.0f, i*100.0f);
    }
    Memory::read();
  }
}


BENCHMARK(push_back);
BENCHMARK(push_back_reserve);
BENCHMARK(emplace_back);
BENCHMARK(emplace_back_reserve);
BENCHMARK(create);
BENCHMARK(reserve);

BENCHMARK(push_backN);
BENCHMARK(push_back_reserveN);
BENCHMARK(emplace_backN);
BENCHMARK(emplace_back_reserveN);
BENCHMARK(reserveN);


BENCHMARK_MAIN();
