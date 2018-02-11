////////////////////////////////////////////////////////////
/// mainwindow.h
///
/// Copyright Jeremiah Pope 2017
////////////////////////////////////////////////////////////

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>

#include <VLCQtCore/Common.h>
#include <VLCQtCore/Instance.h>
#include <VLCQtCore/Media.h>
#include <VLCQtCore/MediaPlayer.h>

#include "device/WheelsDevice.h"
#include "device/ArmDevice.h"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent* e);
    void keyReleaseEvent(QKeyEvent* e);

private slots:
    void on_connectButton_clicked();

    void on_wheelsSlider_valueChanged(int value);
    void on_yawSlider_valueChanged(int value);
    void on_pitchSlider_valueChanged(int value);
    void on_reachSlider_valueChanged(int value);

    void on_controlsHelpMenu_triggered();

private:
    Ui::MainWindow* m_ui;
    WheelsDevice    m_wheels;
    ArmDevice       m_arm;

    VlcInstance*    m_armInstance;
    VlcMedia*       m_armMedia;
    VlcMediaPlayer* m_armPlayer;

    VlcInstance*    m_wheelsInstance;
    VlcMedia*       m_wheelsMedia;
    VlcMediaPlayer* m_wheelsPlayer;
};

#endif // MAINWINDOW_H
