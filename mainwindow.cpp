////////////////////////////////////////////////////////////
/// mainwindow.cpp
///
/// Copyright Jeremiah Pope 2017
////////////////////////////////////////////////////////////

#include <QMessageBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    m_ui(new Ui::MainWindow),
    m_armMedia(0),
    m_wheelsMedia(0)
{
    m_ui->setupUi(this);

    //setCentralWidget(m_ui->horizontalLayoutWidget);

    m_armInstance = new VlcInstance(VlcCommon::args(), this);
    m_armPlayer = new VlcMediaPlayer(m_armInstance);
    m_armPlayer->setVideoWidget(m_ui->armVideo);

    m_wheelsInstance = new VlcInstance(VlcCommon::args(), this);
    m_wheelsPlayer = new VlcMediaPlayer(m_wheelsInstance);
    m_wheelsPlayer->setVideoWidget(m_ui->wheelsVideo);

    m_ui->armVideo->setMediaPlayer(m_armPlayer);
    m_ui->wheelsVideo->setMediaPlayer(m_wheelsPlayer);

    m_wheels.setSpeed(m_ui->wheelsSlider->value());
    m_wheels.setHorizontalSpeed(m_ui->yawSlider->value());

    m_arm.setVerticalSpeed(m_ui->pitchSlider->value());
    m_arm.setExtendSpeed(m_ui->reachSlider->value());

    //showMaximized();
}

MainWindow::~MainWindow()
{
    delete m_armPlayer;
    delete m_armMedia;
    delete m_armInstance;

    delete m_wheelsPlayer;
    delete m_wheelsMedia;
    delete m_wheelsInstance;
}

void MainWindow::keyPressEvent(QKeyEvent* e)
{
    if (e->isAutoRepeat())
    {
        return;
    }

    switch(e->key())
    {
    case Qt::Key_Up:
        m_wheels.moveWheelsForward();
        break;
    case Qt::Key_Down:
        m_wheels.moveWheelsBackward();
        break;
    case Qt::Key_Left:
        m_wheels.moveWheelsLeft();
        break;
    case Qt::Key_Right:
        m_wheels.moveWheelsRight();
        break;
    case Qt::Key_W:
        m_arm.moveArmUp();
        break;
    case Qt::Key_S:
        m_arm.moveArmDown();
        break;
    case Qt::Key_A:
        m_wheels.moveArmLeft();
        break;
    case Qt::Key_D:
        m_wheels.moveArmRight();
        break;
    case Qt::Key_E:
        m_arm.extendArm();
        break;
    case Qt::Key_R:
        m_arm.retractArm();
        break;
    case Qt::Key_L:
        m_arm.turnLaserOn();
        break;
    default:
        break;
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent* e)
{
    if (e->isAutoRepeat())
    {
        return;
    }

    switch(e->key())
    {
    case Qt::Key_Up:
        m_wheels.stopWheels(WheelsDevice::Direction::forward);
        break;
    case Qt::Key_Down:
        m_wheels.stopWheels(WheelsDevice::Direction::backward);
        break;
    case Qt::Key_Left:
        m_wheels.stopWheels(WheelsDevice::Direction::left);
        break;
    case Qt::Key_Right:
        m_wheels.stopWheels(WheelsDevice::Direction::right);
        break;
    case Qt::Key_W:
    case Qt::Key_S:
        m_arm.stopArmVertical();
        break;
    case Qt::Key_A:
    case Qt::Key_D:
        m_wheels.stopArmHorizontal();
        break;
    case Qt::Key_E:
    case Qt::Key_R:
        m_arm.stopExtendArm();
        break;
    case Qt::Key_L:
        m_arm.turnLaserOff();
        break;
    default:
        break;
    }
}

void MainWindow::on_connectButton_clicked()
{
    QString ipWheelsAddress = m_ui->wheelsIPAddressTextBox->text();
    QString ipArmAddress = m_ui->armIPAddressTextBox->text();
    QString username = m_ui->usernameTextBox->text();
    QString password = m_ui->passwordTextBox->text();

    if (ipWheelsAddress.isEmpty() || ipArmAddress.isEmpty())
    {
        QMessageBox msgBox;
        msgBox.setInformativeText("Enter both ip addresses");
        msgBox.exec();
        return;
    }

    if (username.isEmpty() || password.isEmpty())
    {
        QMessageBox msgBox;
        msgBox.setInformativeText("Enter username and password");
        msgBox.exec();
        return;
    }

    m_wheels.connectToDevice(ipWheelsAddress, 1234);
    m_arm.connectToDevice(ipArmAddress, 1234);

    //if (m_arm.isDeviceConnected())
    {
        m_armMedia = new VlcMedia("http://" + username + ":" + password + "@" + ipArmAddress + ":1235/cam_pic_new.php?", m_armInstance);
        if (m_armMedia)
        {
            m_armPlayer->open(m_armMedia);
        }
    }

    //if (m_wheels.isDeviceConnected())
    {
        m_wheelsMedia = new VlcMedia("http://" + username + ":" + password + "@" + ipWheelsAddress + ":1235/cam_pic_new.php?", m_wheelsInstance);
        if (m_wheelsMedia)
        {
            m_wheelsPlayer->open(m_wheelsMedia);
        }
    }

    this->setFocus();
}

void MainWindow::on_wheelsSlider_valueChanged(int value)
{
    m_wheels.setSpeed(value);
    this->setFocus();
}

void MainWindow::on_yawSlider_valueChanged(int value)
{
    m_wheels.setHorizontalSpeed(value);
    this->setFocus();
}

void MainWindow::on_pitchSlider_valueChanged(int value)
{
    m_arm.setVerticalSpeed(value);
    this->setFocus();
}

void MainWindow::on_reachSlider_valueChanged(int value)
{
    m_arm.setExtendSpeed(value);
    this->setFocus();
}

void MainWindow::on_controlsHelpMenu_triggered()
{
    QMessageBox msgBox;
    msgBox.setInformativeText("<b>Wheel Commands</b><br>"
                              "Forward - Up Arrow<br>"
                              "Backward - Back Arrow<br>"
                              "Left - Left Arrow<br>"
                              "Right - Right Arrow<br>"
                              "<br>"
                              "<b>Arm Commands</b><br>"
                              "Up - W<br>"
                              "Down - S<br>"
                              "Left - A<br>"
                              "Right - D<br>"
                              "Extend - E<br>"
                              "Retract - R<br>"
                              "<br>"
                              "<b>Laser Command</b><br>"
                              "Activate - L");
    msgBox.exec();
}
