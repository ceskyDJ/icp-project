# Class and sequence diagram editor

Class and sequence diagram editor is a project to course The C++ Programming Language (ICP)
taught at FIT BUT. It is a multi-platform GUI program for creating and editing class diagrams
and sequence diagrams from UML.

**Authors:**
- Michal Šmahel (xsmahe01)
- Jakub Dvořák (xdvora3q)

## Implemented part of an assignment

The implementation of the project is not complete. There are a few points of the assignment that are not implemented. This section will try to describe all of them.

### Class diagram

Many of the required elements for the class diagram work well. Class diagrams could be created and edited. The user can add the required relationships between the created classes. Classes can be moved around the canvas, selected, and deleted. All class properties are ready for change by the editor widget. Classes and methods could be abstract. The interface is modeled as a class of a special type and is correctly displayed. Sadly, the solution of drawing relationship arrows is not the best. The connector between buttons for undo/redo operations is missing. Marking of the inherited methods is not present. The load and save buttons are not linked with the models, so loading and saving diagrams from/to XML files does not work.

### Sequence diagram

The GUI of the sequence diagram is not created at all.

### Data layer

The term "data layer" means working with raw data like loading and saving to files, constructing entity classes for communication with GUI, etc. This part of the project is fully completed. All things for supporting GUI operations are done. Unlike the GUI part, at the data layer sequence diagrams are also supported. It supports undo/redo operations implemented using a memento design pattern. Collisions between sequence and class diagrams could be detected using the provided methods to find classes and methods by their names. Diagrams could also be loaded from XML files and saved in them.

## Taken parts

The source code of the project is written on our own in most situations. Only custom enumeration classes that add support for adding methods are inspired by the comment from Stack overflow [4]. They are a little more complicated because they contain many operators, a trick with enumeration contained in class namespace, and some other tricks. During data layer programming, the main sources were Cppreference.com [1] and the official slides of the ICP course [6]. For creating our own XML format that is used to persistently store diagrams, a W3 school tutorial was used [3]. For manipulating XML files, a small subset of the Qt toolkit is used, so its documentation was used as a reference [2]. GUI programming required Qt documentation [2] and official slides of the ICP course [6].

## References

1. *C++ reference* [online]. [cit. 2022-05-08]. Available from: https://en.cppreference.com/w/cpp
2. *Qt documentation: Qt 5.15* [online]. c2022 [cit. 2022-05-08]. Available from: https://doc.qt.io/qt-5/
3. *XML Tutorial* [online]. c1999-2022 [cit. 2022-05-08]. Available from: https://www.w3schools.com/xml/
4. jtlim. Can a C++ enum class have methods?. In: Stack overflow [online]. Nov 13, 2018 [cit. 2022-05-08]. Available from: https://stackoverflow.com/a/53284026
5. GAMMA, Erich. Design patterns: elements of reusable object-oriented software. Boston: Addison-Wesley, 1995, 395 s. ISBN 0-201-63361-2.
6. *Seminář C++* [online]. 2022-02. Brno: Petr Peringer, 2022. Available from: http://www.fit.vutbr.cz/study/courses/ICP/public/Prednasky/ICP.pdf
