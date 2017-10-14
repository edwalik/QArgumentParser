###########################################################
#
#   QArgumentParser: Command line argument parser using the QtCore module.
#   Copyright (C) 2017 Nicolas Kogler
#   License: Lesser General Public License 3.0
#
###########################################################

###########################################################
# GENERAL SETTINGS
#
###########################################################
TARGET   = QArgumentParser
TEMPLATE = lib
QT      -= gui
CONFIG  += plugin c++11
DEFINES += QARGUMENTPARSER_BUILD_SHARED

###########################################################
# WINDOWS SETTINGS
#
###########################################################
win32 {
    QMAKE_TARGET_COMPANY     = Nicolas Kogler
    QMAKE_TARGET_PRODUCT     = QArgumentParser
    QMAKE_TARGET_DESCRIPTION = Command line argument parser using the QtCore module
    QMAKE_TARGET_COPYRIGHT   = Copyright (C) 2017 Nicolas Kogler
}

###########################################################
# COMPILER SETTINGS
#
###########################################################
msvc {
    QMAKE_CXXFLAGS += /EHsc
} gcc {
    QMAKE_CXXFLAGS += -fno-exceptions
    QMAKE_LFLAGS += -static-libgcc -static-libstdc++
}

###########################################################
# INCLUDE PATHS
#
###########################################################
INCLUDEPATH += include

###########################################################
# HEADER FILES
#
###########################################################
HEADERS += include/QArgumentParser/Config.hpp \
           include/QArgumentParser/QArgumentOption.hpp \
           include/QArgumentParser/QArgumentValidator.hpp \
           include/QArgumentParser/QArgumentValidatorOption.hpp \
           include/QArgumentParser/QArgumentParser.hpp \
           include/QArgumentParser/QArgumentOption.inl

###########################################################
# SOURCE FILES
#
###########################################################
SOURCES += src/QArgumentOption.cpp \
           src/QArgumentParser.cpp \
           src/QArgumentValidator.cpp \
           src/QArgumentValidatorOption.cpp

################################################################################
## OUTPUT
##
################################################################################
include(platforms/platforms.pri)
message(Writing library to: $${PWD}/bin/$${kgl_path})

DESTDIR     = $${PWD}/bin/$${kgl_path}
OBJECTS_DIR = $${DESTDIR}/obj
MOC_DIR     = $${OBJECTS_DIR}
RCC_DIR     = $${OBJECTS_DIR}
UI_DIR      = $${OBJECTS_DIR}
