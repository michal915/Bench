#include "StateMachinePattern.hpp"
#include "Memory.hpp"

#include <iostream>
#include <memory>

namespace StatePattern
{

TrafficLights::TrafficLights()
{
}

std::shared_ptr<TrafficLights> TrafficLights::makeTrafficLights()
{
  std::shared_ptr<TrafficLights> trafficLights{new TrafficLights{}};
  trafficLights->init();
  return trafficLights;
}

void TrafficLights::init()
{
  mState = std::make_shared<LightRed>(this->shared_from_this());
}

void TrafficLights::setState(std::shared_ptr<MachineState> state)
{
  mState = state;
}

void TrafficLights::processing ()
{
  mState->processing();
}

// green
LightGreen::LightGreen(std::shared_ptr<TrafficLights> context) :
mContext{context}
{
}

void LightGreen::processing()
{
  Memory::read();
  mContext->setState(std::make_shared<LightYellow>(mContext));
}

// red
LightRed::LightRed(std::shared_ptr<TrafficLights> context) :
mContext{context}
{
}

void LightRed::processing()
{
  Memory::read();
  mContext->setState(std::make_shared<LightGreen>(mContext));
}

// yellow
LightYellow::LightYellow(std::shared_ptr<TrafficLights> context) :
mContext{context}
{
}

void LightYellow::processing()
{
  Memory::read();
  mContext->setState(std::make_shared<LightRed>(mContext));
}

} // namespace
