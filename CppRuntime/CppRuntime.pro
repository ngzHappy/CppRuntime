QT += core
QT -= gui

CONFIG += c++14
DEFINES *= LIBRARY_CPP_RUNTIME

CONFIG(debug,debug|release){
TARGET = cpp_lib_runtimed
}else{
TARGET = cpp_lib_runtime
}

TEMPLATE = lib

SOURCES += main.cpp \
    RuntimeType.cpp

HEADERS += \
    RuntimeType.hpp

win32-msvc*{

CONFIG(debug,debug|release){
DESTDIR=$$PWD/../binlib/vs/debug_
}else{
DESTDIR=$$PWD/../binlib/vs/release_
}

}else{

CONFIG(debug,debug|release){
DESTDIR=$$PWD/../binlib/debug_
}else{
DESTDIR=$$PWD/../binlib/release_
}

}

