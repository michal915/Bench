#include "MachineSwitch.hpp"
#include "Memory.hpp"

namespace SwitchMachine
{

TrafficLights::TrafficLights() : mState{TrafficLightsColors::RED}
{
}

void TrafficLights::processing()
{
  switch(mState)
  {
    case RED:
      Memory::read();
      mState = TrafficLightsColors::YELLOW;
    break;
    case YELLOW:
      Memory::read();
      mState = TrafficLightsColors::GREEN;
    break;
    case GREEN:
      Memory::read();
      mState = TrafficLightsColors::RED;
    break;
  }
}

}
