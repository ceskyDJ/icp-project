#include <QApplication>
#include <QPushButton>
#include <ClassDiagramWindow.h>

int main(int argc, char **argv)
{
 QApplication app (argc, argv);

 ClassDiagramWindow classDiagramWindow;

 classDiagramWindow.show();

 return app.exec();
}
