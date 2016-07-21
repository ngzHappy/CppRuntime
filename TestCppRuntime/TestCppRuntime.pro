QT += core
QT -= gui

CONFIG += c++14

TARGET = TestCppRuntime
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    test_void_type.cpp \
    test_static_type_cast.cpp
INCLUDEPATH +=$$PWD/../CppRuntime

win32-msvc*{

CONFIG(debug,debug|release){
LIBS+=-L$$PWD/../binlib/vs/debug_ -lcpp_lib_runtimed
DESTDIR=$$PWD/../binlib/vs/debug_
}else{
LIBS+=-L$$PWD/../binlib/vs/release_ -lcpp_lib_runtime
DESTDIR=$$PWD/../binlib/vs/release_
}

}else{

CONFIG(debug,debug|release){
LIBS+=-L$$PWD/../binlib/debug_ -lcpp_lib_runtimed
DESTDIR=$$PWD/../binlib/debug_
}else{
LIBS+=-L$$PWD/../binlib/release_ -lcpp_lib_runtime
DESTDIR=$$PWD/../binlib/release_
}

}
