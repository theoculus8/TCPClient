#include <QJsonObject>
#include <QJsonArray>
#include "ArmDevice.h"

ArmDevice::ArmDevice()
{
}

ArmDevice::~ArmDevice()
{
    if (isDeviceConnected())
    {
        QJsonArray json;
        QJsonObject verticalDevice;
        verticalDevice["device"] = "arm_pitch_motor";
        verticalDevice["percent"] = 0;
        json.push_back(verticalDevice);
        QJsonObject horizontalDevice;
        horizontalDevice["device"] = "arm_yaw_motor";
        horizontalDevice["percent"] = 0;
        json.push_back(horizontalDevice);
        QJsonObject extendDevice;
        extendDevice["device"] = "arm_reach_motor";
        extendDevice["percent"] = 0;
        json.push_back(extendDevice);

        writeJsonToSocket(json);
    }
}

void ArmDevice::moveArm(QString deviceString, int speed)
{
    QJsonArray json;
    QJsonObject device;
    device["device"] = deviceString;
    device["percent"] = speed;
    json.push_back(device);

    writeJsonToSocket(json);
}

void ArmDevice::moveArmUp()
{
    moveArm("arm_pitch_motor", m_verticalSpeed);
    m_verticalDirection = Direction::forward;
}

void ArmDevice::moveArmDown()
{
    moveArm("arm_pitch_motor", -m_verticalSpeed);
    m_verticalDirection = Direction::backward;
}

void ArmDevice::extendArm()
{
    moveArm("arm_reach_motor", m_extendSpeed);
    m_extendDirection = Direction::forward;
}

void ArmDevice::retractArm()
{
    moveArm("arm_reach_motor", -m_extendSpeed);
    m_extendDirection = Direction::backward;
}

void ArmDevice::stopArmVertical()
{
    moveArm("arm_pitch_motor", 0);
    m_verticalDirection = Direction::stop;
}

void ArmDevice::stopExtendArm()
{
    moveArm("arm_reach_motor", 0);
    m_verticalDirection = Direction::stop;
}

void ArmDevice::setVerticalSpeed(int speed)
{
    m_verticalSpeed = speed;
}

void ArmDevice::setExtendSpeed(int speed)
{
    m_extendSpeed = speed;
}

void ArmDevice::turnLaserOn()
{
    QJsonArray json;
    QJsonObject device;
    device["device"] = "lazer";
    device["percent"] = 100;
    json.push_back(device);

    writeJsonToSocket(json);
}

void ArmDevice::turnLaserOff()
{
    QJsonArray json;
    QJsonObject device;
    device["device"] = "lazer";
    device["percent"] = 0;
    json.push_back(device);

    writeJsonToSocket(json);
}
