#include <QApplication>
#include "ClassDiagramWindow.h"
#include "ClassDiagramManager.h"
#include "FileClassDiagramRepository.h"

int main(int argc, char **argv)
{
    QApplication app{argc, argv};

    // Dependencies
    FileClassDiagramRepository classDiagramRepository{};
    ClassDiagramManager classDiagramManager{&classDiagramRepository};
    SceneUpdateObservable sceneUpdateObservable{};

    ClassDiagramWindow classDiagramWindow{&classDiagramManager, &sceneUpdateObservable};

    classDiagramWindow.showMaximized();

    return app.exec();
}
