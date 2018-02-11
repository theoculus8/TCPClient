#include <QJsonObject>
#include <QJsonArray>
#include <QMutexLocker>
#include "WheelsDevice.h"

WheelsDevice::WheelsDevice()
{
}

WheelsDevice::~WheelsDevice()
{
    if (isDeviceConnected())
    {
        QJsonArray json;
        QJsonObject device1;
        device1["device"] = "chassis_left_motor";
        device1["percent"] = 0;
        QJsonObject device2;
        device2["device"] = "chassis_right_motor";
        device2["percent"] = 0;
        QJsonObject device3;
        device3["device"] = "lazer";
        device3["percent"] = 0;
        json.push_back(device1);
        json.push_back(device2);
        json.push_back(device3);

        writeJsonToSocket(json);
    }
}

void WheelsDevice::sendWheelsCommand(int leftWheelsSpeed, int rightWheelsSpeed)
{
    QJsonArray json;
    QJsonObject device1;
    device1["device"] = "chassis_left_motor";
    device1["percent"] = leftWheelsSpeed;
    QJsonObject device2;
    device2["device"] = "chassis_right_motor";
    device2["percent"] = rightWheelsSpeed;
    json.push_back(device1);
    json.push_back(device2);

    writeJsonToSocket(json);
}

void WheelsDevice::directWheels()
{
    int leftWheelsSpeed;
    int rightWheelsSpeed;
    switch (getDirection())
    {
    case Direction::forward:
        if (m_currentDirection == Direction::forward)
        {
            return;
        }
        m_currentDirection = Direction::forward;
        leftWheelsSpeed = m_speed;
        rightWheelsSpeed = m_speed;
        break;
    case Direction::backward:
        if (m_currentDirection == Direction::backward)
        {
            return;
        }
        m_currentDirection = Direction::backward;
        leftWheelsSpeed = -m_speed;
        rightWheelsSpeed = -m_speed;
        break;
    case Direction::left:
        if (m_currentDirection == Direction::left)
        {
            return;
        }
        m_currentDirection = Direction::left;
        leftWheelsSpeed = -m_speed;
        rightWheelsSpeed = m_speed;
        break;
    case Direction::right:
        if (m_currentDirection == Direction::right)
        {
            return;
        }
        m_currentDirection = Direction::right;
        leftWheelsSpeed = m_speed;
        rightWheelsSpeed = -m_speed;
        break;
    case Direction::stop:
        if (m_currentDirection == Direction::stop)
        {
            return;
        }
        m_currentDirection = Direction::stop;
        leftWheelsSpeed = 0;
        rightWheelsSpeed = 0;
        break;
    }

    sendWheelsCommand(leftWheelsSpeed, rightWheelsSpeed);
}

void WheelsDevice::stopWheels(Direction direction)
{
    removeDirection(direction);
    directWheels();
}

void WheelsDevice::moveWheelsForward()
{
    addDirection(Direction::forward);
    directWheels();
}

void WheelsDevice::moveWheelsBackward()
{
    addDirection(Direction::backward);
    directWheels();
}

void WheelsDevice::moveWheelsLeft()
{
    addDirection(Direction::left);
    directWheels();
}

void WheelsDevice::moveWheelsRight()
{
    addDirection(Direction::right);
    directWheels();
}

void WheelsDevice::setSpeed(int speed)
{
    m_speed = speed;
}

void WheelsDevice::addDirection(Direction direction)
{
    m_directions.append(direction);
}

void WheelsDevice::removeDirection(Direction direction)
{
    m_directions.removeOne(direction);
}

WheelsDevice::Direction WheelsDevice::getDirection()
{
    if (m_directions.isEmpty())
    {
        return Direction::stop;
    }
    else
    {
        return m_directions.last();
    }
}

void WheelsDevice::moveArmLeft()
{
    QJsonArray json;
    QJsonObject device;
    device["device"] = "arm_yaw_motor";
    device["percent"] = m_horizonalSpeed;
    json.push_back(device);

    writeJsonToSocket(json);

    m_horizontalDirection = Direction::forward;
}

void WheelsDevice::moveArmRight()
{
    QJsonArray json;
    QJsonObject device;
    device["device"] = "arm_yaw_motor";
    device["percent"] = -m_horizonalSpeed;
    json.push_back(device);

    writeJsonToSocket(json);

    m_horizontalDirection = Direction::backward;
}

void WheelsDevice::stopArmHorizontal()
{
    QJsonArray json;
    QJsonObject device;
    device["device"] = "arm_yaw_motor";
    device["percent"] = 0;
    json.push_back(device);

    writeJsonToSocket(json);

    m_horizontalDirection = Direction::stop;
}

void WheelsDevice::setHorizontalSpeed(int speed)
{
    m_horizonalSpeed = speed;
}
