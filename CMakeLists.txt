cmake_minimum_required(VERSION 3.22)
project(icp_project)

set(CMAKE_SOURCE_DIR src/)
set(PROJECT_BINARY_DIR ../build/bin/)
set(CMAKE_BINARY_DIR ../build/bin/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../build/bin/)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/usr/lib/x86_64-linux-gnu/qt5/")

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        Xml
        REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_executable(icp_project
        # Header files
        src/ActivationGraphicsObjectBase.h
        src/ActivationObjectEmitter.h
        src/ActorGraphicsItem.h
        src/ActorGraphicsItemEditDialog.h
        src/AgregationLine.h
        src/AssociationLine.h
        src/AssociationLineEditDialog.h
        src/AsyncMessageLine.h
        src/ClassDiagram.h
        src/ClassNodeEmitter.h
        src/ClassDiagramScene.h
        src/CustomScene.h
        src/CreateMessageLine.h
        src/DestroyMessageLine.h
        src/DirectedAssociationLine.h
        src/DirectedAssociationLineEditDialog.h
        src/EditDialogBase.h
        src/Line.h
        src/LineWithArrow.h
        src/LineWithArrowEditDialog.h
        src/MessageLine.h
        src/MessageLineEditDialog.h
        src/MethodParameterEditWidget.h
        src/ObjectGraphicsItem.h
        src/ObjectGraphicsItemEditDialog.h
        src/RealizationLine.h
        src/ReplyMessageLine.h
        src/SequenceDiagram.h
        src/SequenceDiagramScene.h
        src/ClassMember.h
        src/ClassMethod.h
        src/ClassAttribute.h
        src/Class.h
        src/Object.h
        src/MethodParameter.h
        src/Message.h
        src/Relationship.h
        src/Generalization.h
        src/Aggregation.h
        src/Composition.h
        src/AccessModifier.h
        src/ClassType.h
        src/MessageType.h
        src/Actor.h
        src/ClassMethodType.h
        src/SyncMessageLine.h
        src/UndirectedAssociation.h
        src/DirectedAssociation.h
        src/MessageNode.h
        src/Realization.h
        src/ClassDiagramRepository.h
        src/FileClassDiagramRepository.h
        src/SequenceDiagramRepository.h
        src/FileSequenceDiagramRepository.h
        src/AppException.h
        src/InvalidDataStorageException.h
        src/InvalidInputDataException.h
        src/MethodReference.h
        src/ClassDiagramManager.h
        src/SequenceDiagramManager.h
        src/HistoryStack.h
        src/ClassDiagramMemento.h
        src/SequenceDiagramMemento.h
        src/MainWindow.h
        src/MethodParameterEditWidget.h
        src/Line.h
        src/classNode.h
        src/ClassEditDialog.h
        src/AttributeEditWidget.h
        src/MethodEditWidget.h
        src/CompositionLine.h
        src/GeneralizationLine.h
        src/SceneUpdateObserver.h
        src/SceneUpdateObservable.h
        src/TabWidget.h
        src/ReferenceUpdater.h

        # Source files
        src/AccessModifier.cpp
        src/ActivationGraphicsObjectBase.cpp
        src/ActivationObjectEmitter.cpp
        src/ActorGraphicsItem.cpp
        src/ActorGraphicsItemEditDialog.cpp
        src/AgregationLine.cpp
        src/AssociationLine.cpp
        src/AssociationLineEditDialog.cpp
        src/ClassMethodType.cpp
        src/ClassNodeEmitter.cpp
        src/ClassType.cpp
        src/ClassDiagramScene.cpp
        src/CustomScene.cpp
        src/CreateMessageLine.cpp
        src/DestroyMessageLine.cpp
        src/DirectedAssociationLine.cpp
        src/DirectedAssociationLineEditDialog.cpp
        src/EditDialogBase.cpp
        src/LineWithArrow.cpp
        src/LineWithArrowEditDialog.cpp
        src/MessageLine.cpp
        src/MessageLineEditDialog.cpp
        src/MessageType.cpp
        src/ClassDiagram.cpp
        src/ObjectGraphicsItem.cpp
        src/ObjectGraphicsItemEditDialog.cpp
        src/RealizationLine.cpp
        src/ReplyMessageLine.cpp
        src/SequenceDiagram.cpp
        src/SequenceDiagramScene.cpp
        src/Class.cpp
        src/FileClassDiagramRepository.cpp
        src/FileSequenceDiagramRepository.cpp
        src/ClassDiagramManager.cpp
        src/SequenceDiagramManager.cpp
        src/MainWindow.cpp
        src/MethodParameterEditWidget.cpp
        src/Line.cpp
        src/SyncMessageLine.cpp
        src/classNode.cpp
        src/ClassEditDialog.cpp
        src/AttributeEditWidget.cpp
        src/MethodEditWidget.cpp
        src/CompositionLine.cpp
        src/GeneralizationLine.cpp
        src/TabWidget.cpp
        src/main.cpp

        # Qrc files
        rsc.qrc)
target_link_libraries(icp_project
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Xml)

add_executable(test_save_class_diagram
        test/save-class-diagram.cpp src/ClassDiagram.h src/SequenceDiagram.h src/ClassMember.h src/ClassMethod.h
        src/ClassAttribute.h src/Class.h src/Object.h src/MethodParameter.h src/Message.h src/Relationship.h
        src/Generalization.h src/Aggregation.h src/Composition.h src/AccessModifier.h src/ClassType.h src/MessageType.h
        src/Actor.h src/ClassMethodType.h src/UndirectedAssociation.h src/DirectedAssociation.h src/MessageNode.h
        src/AccessModifier.cpp src/ClassMethodType.cpp src/ClassType.cpp src/MessageType.cpp src/Realization.h
        src/ClassDiagram.cpp src/SequenceDiagram.cpp src/ClassDiagramRepository.h src/FileClassDiagramRepository.cpp
        src/FileClassDiagramRepository.h src/SequenceDiagramRepository.h src/FileSequenceDiagramRepository.cpp
        src/FileSequenceDiagramRepository.h src/InvalidDataStorageException.h src/AppException.h
        src/InvalidInputDataException.h src/Class.cpp)
target_link_libraries(test_save_class_diagram
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Xml)

add_executable(test_save_sequence_diagram
        test/save-sequence-diagram.cpp src/ClassDiagram.h src/SequenceDiagram.h src/ClassMember.h src/ClassMethod.h
        src/ClassAttribute.h src/Class.h src/Object.h src/MethodParameter.h src/Message.h src/Relationship.h
        src/Generalization.h src/Aggregation.h src/Composition.h src/AccessModifier.h src/ClassType.h src/MessageType.h
        src/Actor.h src/ClassMethodType.h src/UndirectedAssociation.h src/DirectedAssociation.h src/MessageNode.h
        src/AccessModifier.cpp src/ClassMethodType.cpp src/ClassType.cpp src/MessageType.cpp src/Realization.h
        src/ClassDiagram.cpp src/AccessModifier.cpp src/ClassMethodType.cpp src/ClassType.cpp src/MessageType.cpp
        src/Realization.h src/ClassDiagramRepository.h src/FileClassDiagramRepository.cpp
        src/FileClassDiagramRepository.h src/SequenceDiagramRepository.h src/FileSequenceDiagramRepository.cpp
        src/FileSequenceDiagramRepository.h src/InvalidDataStorageException.h src/AppException.h
        src/InvalidInputDataException.h src/SequenceDiagram.cpp src/ClassReference.h src/MethodReference.h
        src/Class.cpp)
target_link_libraries(test_save_sequence_diagram
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Xml)

target_compile_options(icp_project PRIVATE -g -pedantic -Wall -Wextra -Werror)
