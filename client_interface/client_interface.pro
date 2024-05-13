QT       += core gui \
    quick
QT -= gui


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
CONFIG += c++11 console
CONFIG -= app_bundle
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
DEFINES += QT_DEPRECATED_WARNINGS    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    SHA512.cpp \
    dialog_reg.cpp \
    func_for_client.cpp \
    main.cpp \
    mainwindow.cpp \
    navigation_page.cpp \
    singletonclient.cpp

HEADERS += \
    SHA512.h \
    dialog_reg.h \
    func_for_client.h \
    mainwindow.h \
    navigation_page.h \
    singletonclient.h

FORMS += \
    dialog_reg.ui \
    mainwindow.ui \
    navigation_page.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
