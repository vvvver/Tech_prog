QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_test1.cpp \
../client_interface/SHA512.cpp

HEADERS += \
    ../client_interface/SHA512.h
