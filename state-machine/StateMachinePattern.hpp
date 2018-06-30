#pragma once
#include <memory>

namespace StatePattern
{

class MachineState
{
public:
     virtual void processing() = 0;
};

class TrafficLights : public std::enable_shared_from_this<TrafficLights>
{
    friend class LightGreen;
    friend class LightRed;
    friend class LightYellow;
  private:
    std::shared_ptr<MachineState> mState;
    TrafficLights();
    void init();
public:
    void setState(std::shared_ptr<MachineState> state);
    void processing();

    static std::shared_ptr<TrafficLights> makeTrafficLights();
};

class LightGreen: public MachineState
{
    std::shared_ptr<TrafficLights> mContext;
public:
    LightGreen(std::shared_ptr<TrafficLights> context);
    void processing();
};

class LightRed: public MachineState
{
    std::shared_ptr<TrafficLights> mContext;
public:
    LightRed(std::shared_ptr<TrafficLights> context);
    void processing();
};

class LightYellow: public MachineState
{
    std::shared_ptr<TrafficLights> mContext;
public:
    LightYellow(std::shared_ptr<TrafficLights> context);
    void processing();
};

}
