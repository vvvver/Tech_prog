QT       += core gui
QT -= gui
QT += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
CONFIG += c++11 console
CONFIG -= app_bundle
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
DEFINES += QT_DEPRECATED_WARNINGS    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dialog_reg.cpp \
    funcions_server.cpp \
    main.cpp \
    mainwindow.cpp \
    mytcpserver.cpp \
    test_win.cpp

HEADERS += \
    dialog_reg.h \
    funcions_server.h \
    mainwindow.h \
    mytcpserver.h \
    test_win.h

FORMS += \
    dialog_reg.ui \
    mainwindow.ui \
    test_win.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
