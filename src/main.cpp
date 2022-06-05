#include <QApplication>
#include "MainWindow.h"
#include "ClassDiagramManager.h"
#include "FileClassDiagramRepository.h"
#include "FileSequenceDiagramRepository.h"

int main(int argc, char **argv)
{
    QApplication app{argc, argv};

    // Dependencies
    FileClassDiagramRepository classDiagramRepository{};
    FileSequenceDiagramRepository sequenceDiagramRepository{};
    ClassDiagramManager classDiagramManager{&classDiagramRepository};
    SequenceDiagramManager sequenceDiagramManager{&sequenceDiagramRepository};

    SceneUpdateObservable sceneUpdateObservable{};

    MainWindow mainWindow{&classDiagramManager, &sequenceDiagramManager, &sceneUpdateObservable};

    mainWindow.showMaximized();

    return app.exec();
}
