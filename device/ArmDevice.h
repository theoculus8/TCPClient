#pragma once

#include "Device.h"

class ArmDevice : public Device
{

public:
    enum class Direction
    {
        forward,
        backward,
        stop
    };

    ArmDevice();
    ~ArmDevice();

    void moveArmUp();
    void moveArmDown();
    void extendArm();
    void retractArm();

    void stopArmVertical();
    void stopExtendArm();

    void setVerticalSpeed(int speed);
    void setExtendSpeed(int speed);

    void turnLaserOn();
    void turnLaserOff();

private:
    void moveArm(QString deviceString, int speed);

    int m_verticalSpeed;
    int m_extendSpeed;

    Direction m_verticalDirection = Direction::stop;
    Direction m_extendDirection   = Direction::stop;
};
