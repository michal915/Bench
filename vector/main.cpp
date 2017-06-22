#include <benchmark/benchmark.h>
#include <string>
#include <vector>

class Test {
  float mX, mY, mZ;
  std::string mTitle;

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

constexpr std::size_t N = 1000;

// Define another benchmark
static void push_back(benchmark::State& state) {
  while (state.KeepRunning())
  {
    std::vector<Test> v;
    for(std::size_t i = 0; i < N; i++)
    {
      v.push_back(Test("test", i, i*10.0f, i*100.0f));
    }
  }
}

static void push_back_reserve(benchmark::State& state) {
  while (state.KeepRunning())
  {
    std::vector<Test> v;
    v.reserve(N);
    for(std::size_t i = 0; i < N; i++)
    {
      v.push_back(Test("test", i, i*10.0f, i*100.0f));
    }
  }
}


static void emplace_back_reserve(benchmark::State& state) {
  while (state.KeepRunning())
  {
    std::vector<Test> v;
    v.reserve(N);
    for(std::size_t i = 0; i < N; i++)
    {
      v.emplace_back("test", i, i*10.0f, i*100.0f);
    }
  }
}

static void emplace_back(benchmark::State& state) {
  while (state.KeepRunning())
  {
    std::vector<Test> v;
    for(std::size_t i = 0; i < N; i++)
    {
      v.emplace_back("test", i, i*10.0f, i*100.0f);
    }
  }
}

BENCHMARK(push_back);
BENCHMARK(push_back_reserve);
BENCHMARK(emplace_back);
BENCHMARK(emplace_back_reserve);

BENCHMARK_MAIN();
