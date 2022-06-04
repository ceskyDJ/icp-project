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
QT += core gui widgets xml
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
    AgregationLine.h \
    AssociationLine.h \
    AssociationLineEditDialog.h \
    ClassDiagram.h \
    ClassNodeEmitter.h \
    DirectedAssociationLine.h \
    DirectedAssociationLineEditDialog.h \
    Line.h \
    LineWithArrow.h \
    LineWithArrowEditDialog.h \
    MethodParameterEditWidget.h \
    RealizationLine.h \
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
    Realization.h \
    ClassDiagramRepository.h \
    FileClassDiagramRepository.h \
    SequenceDiagramRepository.h \
    FileSequenceDiagramRepository.h \
    AppException.h \
    InvalidDataStorageException.h \
    InvalidInputDataException.h \
    MethodReference.h \
    ClassDiagramManager.h \
    SequenceDiagramManager.h \
    HistoryStack.h \
    ClassDiagramMemento.h \
    SequenceDiagramMemento.h \
    MainWindow.h \
    MethodParameterEditWidget.h \
    Line.h \
    classNode.h \
    ClassEditDialog.h \
    AttributeEditWidget.h \
    MethodEditWidget.h \
    CompositionLine.h \
    GeneralizationLine.h \
    SceneUpdateObserver.h \
    SceneUpdateObservable.h

SOURCES += \
    AccessModifier.cpp \
    AgregationLine.cpp \
    AssociationLine.cpp \
    AssociationLineEditDialog.cpp \
    ClassMethodType.cpp \
    ClassNodeEmitter.cpp \
    ClassType.cpp \
    DirectedAssociationLine.cpp \
    DirectedAssociationLineEditDialog.cpp \
    LineWithArrow.cpp \
    LineWithArrowEditDialog.cpp \
    MessageType.cpp \
    ClassDiagram.cpp \
    RealizationLine.cpp \
    SequenceDiagram.cpp \
    Class.cpp \
    FileClassDiagramRepository.cpp \
    FileSequenceDiagramRepository.cpp \
    ClassDiagramManager.cpp \
    SequenceDiagramManager.cpp \
    MainWindow.cpp \
    MethodParameterEditWidget.cpp \
    Line.cpp \
    classNode.cpp \
    ClassEditDialog.cpp \
    AttributeEditWidget.cpp \
    MethodEditWidget.cpp \
    CompositionLine.cpp \
    GeneralizationLine.cpp \
    main.cpp
