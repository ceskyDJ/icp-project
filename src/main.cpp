#include <QApplication>
#include "ClassDiagramWindow.h"
#include "ClassDiagramManager.h"
#include "FileClassDiagramRepository.h"

int main(int argc, char **argv)
{
    QApplication app{argc, argv};

    FileClassDiagramRepository classDiagramRepository{};
    ClassDiagramManager classDiagramManager{&classDiagramRepository};

    ClassDiagramWindow classDiagramWindow{&classDiagramManager};

    classDiagramWindow.showMaximized();

    return app.exec();
}
