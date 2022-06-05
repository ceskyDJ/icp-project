#include <QApplication>
#include "MainWindow.h"
#include "ClassDiagramManager.h"
#include "FileClassDiagramRepository.h"

int main(int argc, char **argv)
{
    QApplication app{argc, argv};

    // Dependencies
    FileClassDiagramRepository classDiagramRepository{};
    ClassDiagramManager classDiagramManager{&classDiagramRepository};
    SceneUpdateObservable sceneUpdateObservable{};

    MainWindow mainWindow{&classDiagramManager, &sceneUpdateObservable};

    mainWindow.showMaximized();

    return app.exec();
}
