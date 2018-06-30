#pragma once

namespace SwitchMachine
{

enum TrafficLightsColors
{
  RED,
  YELLOW,
  GREEN
};

class TrafficLights
{
  TrafficLightsColors mState;

public:

  TrafficLights();

  void processing();

};

}
