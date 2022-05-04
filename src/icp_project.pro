# Qt Make for project source files
#
# ICP project (Class and sequence diagram editor)
#
# Author: Michal Šmahel (xsmahe01)

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

# Program configuration
TARGET = icp_project

# Source codes
HEADERS += src/ClassDiagram.h src/SequenceDiagram.h src/ClassMember.h src/ClassMethod.h src/ClassAttribute.h \
    src/Class.h src/Object.h src/MethodParameter.h src/Message.h src/Relationship.h src/Generalization.h \
    src/Aggregation.h src/Composition.h src/AccessModifier.h src/ClassType.h src/MessageType.h src/Actor.h \
    src/ClassMethodType.h src/UndirectedAssociation.h src/DirectedAssociation.h src/MessageSender.h

SOURCES += main.cpp

FORMS +=
