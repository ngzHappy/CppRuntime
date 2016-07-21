QT += core
QT -= gui

CONFIG += c++14

TARGET = CppRuntime
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    RuntimeType.cpp

HEADERS += \
    RuntimeType.hpp





