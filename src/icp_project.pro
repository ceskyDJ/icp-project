# Qt Make for project source files
#
# ICP project (Class and sequence diagram editor)
#
# Author: Michal Šmahel (xsmahe01)

# Project configuration
TEMPLATE = app
RESOURCES = ../rsc.qrc
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
    Line.h \
    MethodParameterEditWidget.h \
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
    Aggregation.h \
    Composition.h \
    AccessModifier.h \
    ClassType.h \
    MessageType.h \
    Actor.h \
    ClassMethodType.h \
    UndirectedAssociation.h \
    DirectedAssociation.h \
    MessageNode.h \
    Realization.h
    ClassDiagramRepository.h \
    FileClassDiagramRepository.h \
    SequenceDiagramRepository.h \
    FileSequenceDiagramRepository.h \
    AppException.h \
    InvalidDataStorageException.h \
    InvalidInputDataException.h \
    ObjectReference.h \
    MethodReference.h \
    ClassDiagramManager.h \
    SequenceDiagramManager.h \
    HistoryStack.h \
    ClassDiagramMemento.h \
    SequenceDiagramMemento.h \
    ClassDiagramWindow.h \
    MethodParameterEditWidget.h \
    Line.h \
    ClassEditDialog.h \
    AttributeEditWidget.h \
    MethodEditWidget.h \
    AgregationLine.h \
    CompositionLine.h \
    GeneralizationLine.h

SOURCES += \
    AccessModifier.cpp \
    ClassMethodType.cpp \
    ClassType.cpp \
    MessageType.cpp \
    ClassDiagram.cpp \
    SequenceDiagram.cpp \
    Class.cpp \
    FileClassDiagramRepository.cpp \
    FileSequenceDiagramRepository.cpp \
    ClassDiagramManager.cpp \
    SequenceDiagramManager.cpp \
    ClassDiagramWindow.cpp \
    MethodParameterEditWidget.cpp \
    Line.cpp \
    classNode.cpp \
    ClassEditDialog.cpp \
    AttributeEditWidget.cpp \
    MethodEditWidget.cpp \
    AgregationLine.cpp \
    CompositionLine.cpp \
    GeneralizationLine.cpp \
    main.cpp
