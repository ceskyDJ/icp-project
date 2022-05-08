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

set(CMAKE_PREFIX_PATH "/opt/Qt/5.12.12/gcc_64")

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        Xml
        REQUIRED)

add_executable(icp_project
        src/main.cpp src/ClassDiagram.h src/SequenceDiagram.h src/ClassMember.h src/ClassMethod.h src/ClassAttribute.h
        src/Class.h src/Object.h src/MethodParameter.h src/Message.h src/Relationship.h src/Generalization.h
        src/Aggregation.h src/Composition.h src/AccessModifier.h src/ClassType.h src/MessageType.h src/Actor.h
        src/ClassMethodType.h src/UndirectedAssociation.h src/DirectedAssociation.h src/MessageNode.h
        src/AccessModifier.cpp src/ClassMethodType.cpp src/ClassType.cpp src/MessageType.cpp src/Realization.h
        src/ClassDiagram.cpp src/SequenceDiagram.cpp src/ClassDiagramRepository.h src/FileClassDiagramRepository.cpp
        src/FileClassDiagramRepository.h src/SequenceDiagramRepository.h src/FileSequenceDiagramRepository.cpp
        src/FileSequenceDiagramRepository.h src/InvalidDataStorageException.h src/AppException.h
        src/InvalidInputDataException.h src/SequenceDiagram.cpp src/ClassReference.h src/MethodReference.h src/Class.cpp
        src/ClassDiagramManager.cpp src/ClassDiagramManager.h src/SequenceDiagramManager.cpp
        src/SequenceDiagramManager.h src/HistoryStack.h src/ClassDiagramMemento.h src/SequenceDiagramMemento.h)
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
        src/InvalidInputDataException.h src/SequenceDiagram.cpp src/ClassReference.h src/MethodReference.h src/Class.cpp)
target_link_libraries(test_save_sequence_diagram
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Xml)

target_compile_options(icp_project PRIVATE -g -pedantic -Wall -Wextra -Werror)
