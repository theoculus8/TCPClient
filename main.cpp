////////////////////////////////////////////////////////////
/// main.cpp
///
/// Copyright Jeremiah Pope 2017
////////////////////////////////////////////////////////////

#include "MainWindow.h"
#include <QApplication>
//#include <QMediaPlayer>
//#include <QHBoxLayout>
//#include <QVideoWidget>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setFocus();
    w.show();

    return a.exec();
}
