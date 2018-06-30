#include "StateMachinePattern.hpp"
#include "MachineSwitch.hpp"

#include <benchmark/benchmark.h>
#include <string>
#include <iostream>
#include <memory>

class MachineState
{
public:
     virtual void processing() = 0;
};


static void statePattern(benchmark::State& state)
{
  auto trafficLights = StatePattern::TrafficLights::makeTrafficLights();
  while(state.KeepRunning())
  {
    trafficLights->processing();
  }
}

static void stateSwitch(benchmark::State& state)
{
   SwitchMachine::TrafficLights trafficLights;
   while(state.KeepRunning())
   {
     trafficLights.processing();
   }
 }

BENCHMARK(stateSwitch);
BENCHMARK(statePattern);



BENCHMARK_MAIN();
