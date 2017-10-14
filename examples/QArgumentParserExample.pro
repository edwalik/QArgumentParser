QT -= gui

TARGET = QArgumentParserExample
CONFIG += c++11 console
CONFIG -= app_bundle
SOURCES += main.cpp

win32 {
    QMAKE_TARGET_COMPANY     = Nicolas Kogler
    QMAKE_TARGET_PRODUCT     = QArgumentParser
    QMAKE_TARGET_DESCRIPTION = Command line argument parser using the QtCore module
    QMAKE_TARGET_COPYRIGHT   = Copyright (C) 2017 Nicolas Kogler
} msvc {
    QMAKE_CXXFLAGS += /EHsc
} gcc {
    QMAKE_CXXFLAGS += -fno-exceptions
    QMAKE_LFLAGS += -static-libgcc -static-libstdc++
}

INCLUDEPATH += ../include

include(../platforms/platforms.pri)
message(Linking to: $${PWD}/../bin/$${kgl_path})

LIBS       += -L$${PWD}/../bin/$${kgl_path} -lQArgumentParser
DESTDIR     = $${PWD}/bin/$${kgl_path}
OBJECTS_DIR = $${DESTDIR}/obj
MOC_DIR     = $${OBJECTS_DIR}
RCC_DIR     = $${OBJECTS_DIR}
UI_DIR      = $${OBJECTS_DIR}
