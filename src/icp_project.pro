# Qt Make for project source files
#
# ICP project (Class and sequence diagram editor)
#
# Author: Michal Šmahel (xsmahe01)

# Project configuration
TEMPLATE = app
RESOURCES = rsc.qrc
TARGET = icp_project

# Qt configuration
QT += core gui widgets
CONFIG += debug

# Paths
DESTDIR = ../build/bin  # Binaries
OBJECTS_DIR = ../build/objs  # C++ object files
MOC_DIR = ../build/moc  # Qt's moc files
RCC_DIR = ../build/rcc  # Qt's Resource Compiler output files
UI_DIR = ../builld/ui  # Qt's uic files

# Compile configuration
# Default: -g -Wall -Wextra (+ some other but not important for this configuration)
QMAKE_CXXFLAGS += -std=c++17 -pedantic -Werror

# Source codes
HEADERS += \
    ClassDiagram.h \
    SequenceDiagram.h \
    ClassMember.h \
    ClassMethod.h \
    ClassAttribute.h \
    Class.h \
    Object.h \
    MethodParameter.h \
    Message.h \
    Relationship.h \
    Generalization.h \
    src/Aggregation.h \
    src/Composition.h \
    src/AccessModifier.h \
    src/ClassType.h \
    src/MessageType.h \
    src/Actor.h \
    src/ClassMethodType.h \
    src/UndirectedAssociation.h \
    src/DirectedAssociation.h \
    src/MessageSender.h

SOURCES += \
    main.cpp
