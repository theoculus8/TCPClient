#pragma once

#include <QList>
#include "Device.h"

class WheelsDevice : public Device
{
public:
    enum class Direction
    {
        forward,
        backward,
        left,
        right,
        stop
    };

    WheelsDevice();
    ~WheelsDevice();

    void stopWheels(Direction direction);
    void moveWheelsForward();
    void moveWheelsBackward();
    void moveWheelsLeft();
    void moveWheelsRight();    

    void moveArmLeft();
    void moveArmRight();

    void stopArmHorizontal();

    void setHorizontalSpeed(int speed);

    void setSpeed(int speed);

private:
    // Directions are contained on a stack, so pressing forward key, then pressing left key, then releasing left key
    // results in going forward, then left, then forward
    void addDirection(Direction direction);
    void removeDirection(Direction direction);
    Direction getDirection();

    void directWheels();
    void sendWheelsCommand(int leftWheelsSpeed, int rightWheelsSpeed);

    int              m_speed;
    QList<Direction> m_directions;
    Direction        m_currentDirection = Direction::stop;    

    int       m_horizonalSpeed;
    Direction m_horizontalDirection = Direction::stop;
};
