QT             += core gui network widgets
LIBS           += -pthread
QMAKE_CXXFLAGS += -std=c++14

TARGET = TCPClient
TEMPLATE = app

SOURCES += \
        main.cpp \
        mainwindow.cpp \
        tcp/TCPConnection.cpp \
        device/Device.cpp \
        device/WheelsDevice.cpp \
        device/ArmDevice.cpp

HEADERS += \
        mainwindow.h \
        tcp/TCPConnection.h \
        device/Device.h \
        device/WheelsDevice.h \
        device/ArmDevice.h

FORMS += \
        mainwindow.ui

DISTFILES += \
        certificate/server.crt

VLC_PATH=$$PWD/VLC

LIBS += -L$$VLC_PATH/bin

Release:LIBS += -lVLCQtCore -lVLCQtWidgets
Debug:LIBS += -lVLCQtCored -lVLCQtWidgetsd

INCLUDEPATH += $$VLC_PATH/include