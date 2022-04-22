/**
 * @file
 * File description (short information about what is inside)
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Michal Šmahel (xsmahe01)
 */
#include <QApplication>
#include <QPushButton>

/**
 * Runs a program
 *
 * @param argc Number of input arguments
 * @param argv C-like array of input arguments
 * @return Exit code
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QPushButton button("Hello world!", nullptr);

    button.resize(200, 100);
    button.show();

    return QApplication::exec();
}
