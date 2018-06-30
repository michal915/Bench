#include <benchmark/benchmark.h>
#include <string>

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


class String
{
  std::string mS;

public:

  void setMove(std::string s)
  {
    mS = std::move(s);
  }

  void setcRef(const std::string& s)
  {
    mS = s;
  }

  void setCopy(const std::string s)
  {
    mS = s;
  }

  void setOverl(std::string&& s)
  {
    mS = s;
  }

  void setOverl(const std::string& s)
  {
    mS = s;
  }

};

#define STRING_DATA "tests43535454g5%T656644ttringdfwrgfgrgtgtesrghetet" \

static void moveL(benchmark::State& state) {

  while(state.KeepRunning())
  {
    std::string test = STRING_DATA;
    String s;
    s.setMove(test);
  }
}

static void moveR(benchmark::State& state) {

  while(state.KeepRunning())
  {
    String s;
    s.setMove(STRING_DATA);
  }
}

static void crefL(benchmark::State& state) {

  while(state.KeepRunning())
  {
    std::string test = STRING_DATA;
    String s;
    s.setcRef(test);
  }
}

static void crefR(benchmark::State& state) {

  while(state.KeepRunning())
  {
    String s;
    s.setcRef(STRING_DATA);
  }
}

static void cpyL(benchmark::State& state) {

  while(state.KeepRunning())
  {
    std::string test = STRING_DATA;
    String s;
    s.setCopy(test);
  }
}

static void cpyR(benchmark::State& state) {

  while(state.KeepRunning())
  {
    String s;
    s.setCopy(STRING_DATA);
  }
}

static void ovrlL(benchmark::State& state) {

  while(state.KeepRunning())
  {
    std::string test = STRING_DATA;
    String s;
    s.setOverl(test);
  }
}

static void ovrlR(benchmark::State& state) {

  while(state.KeepRunning())
  {
    String s;
    s.setOverl(STRING_DATA);
  }
}

BENCHMARK(moveL);
BENCHMARK(moveR);
BENCHMARK(crefL);
BENCHMARK(crefR);
BENCHMARK(cpyL);
BENCHMARK(cpyR);
BENCHMARK(ovrlL);
BENCHMARK(ovrlR);



BENCHMARK_MAIN();
