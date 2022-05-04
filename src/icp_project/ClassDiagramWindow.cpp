/**
 * @file ClassDiagramWindow.cpp
 * Implementace třídy, která má z úkol vytvořit okno
 * pro kreslení UML diagramů tříd.
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 */
#include <QPushButton>
#include <QResource>
#include "ClassDiagramWindow.h"

ClassDiagramWindow::ClassDiagramWindow()
{
    initializeComponents();
    setTooBox();
    setTaskBars();
    setMainWindow();
}
void ClassDiagramWindow::initializeComponents()
{
    taskBar =  addToolBar("TaskBar");
    diagramTabs = new QToolBar();
    toolBox = new QToolBox;
    agregationLineWidget = prepareToolItem(QIcon{":/agLine.png"}, "Agregace");
    fellowshipLineWidget = prepareToolItem(QIcon{":/coLine.png"}, "Kompozice");
    compositionLineWidget = prepareToolItem(QIcon{":/feLine.png"}, "Asociace");
    generalisationLineWidget = prepareToolItem(QIcon{":/geLine.png"}, "Generalizace");
    classShapeWidget = prepareToolItem(QIcon{":/classShape.png"}, "Třída");
}

void ClassDiagramWindow::setMainWindow()
{
    classDiagramView = new QGraphicsView(this);     // parent
    classDiagramScene = new QGraphicsScene(classDiagramView);
    QGridLayout *windowLayout = new QGridLayout;

    windowLayout->addWidget(toolBox,0,0);
    windowLayout->addWidget(classDiagramView,0,1);
    windowLayout->addWidget(diagramTabs,1,0);

    classDiagramCenterWidget = new QWidget;
    classDiagramCenterWidget->setLayout(windowLayout);

    setCentralWidget(classDiagramCenterWidget);
    this->setMinimumSize(800,600);
    this->setWindowTitle("UML Class Creator");
}

void ClassDiagramWindow::setTaskBars()
{
    taskBar->addAction("Open");
    taskBar->addAction("Save");
    taskBar->addAction("Save as...");
    taskBar->addAction("Undo");
    taskBar->addAction("Redo");


    //diagramTabs->addWidget(prepareSequencDiagramTab(QIcon(":/closeCross.png"), "Třídní diagram")); //TODO
    diagramTabs->addAction("Sekvenční 1");
    diagramTabs->addAction("Sekvenční 2");
}


QWidget *ClassDiagramWindow::prepareToolItem(QIcon icon, QString labelString)
{
    QToolButton *newToolButton = new QToolButton;
    newToolButton->setIcon(icon);
    newToolButton->setIconSize(QSize(toolboxItemSize, toolboxItemSize));
    newToolButton->setMaximumSize(toolboxItemSize, toolboxItemSize);
    newToolButton->setMinimumSize(toolboxItemSize, toolboxItemSize);

    QVBoxLayout *toolboxItemLayout = new QVBoxLayout();
    toolboxItemLayout->addWidget(newToolButton);
    QLabel *label = new QLabel(labelString);
    toolboxItemLayout->addWidget(label);

    QWidget* toolboxItem = new QWidget;
    toolboxItem->setLayout(toolboxItemLayout);
    //toolboxItem->setMaximumSize(toolboxItemSize, toolboxItemSize + label->size().height() + 20);
    return toolboxItem;
}

QWidget *ClassDiagramWindow::prepareSequencDiagramTab(QIcon icon, QString label)
{
    QWidget *newTab = new QWidget;
    QWidget *picture = new QWidget();

    QGridLayout *actionLayout = new QGridLayout();
    actionLayout->addWidget(newTab,0,0);
    actionLayout->addWidget(new QLabel(label),0,1);
    return newTab;
}


void ClassDiagramWindow::setTooBox()
{
    toolBox->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Ignored));
    toolBox->setMinimumWidth(minToolboxWidth);
    QGroupBox *toolboxItems = new QGroupBox;
    QGridLayout *toolboxLayout = new QGridLayout;
    toolboxLayout->addWidget(agregationLineWidget, 0, 0);
    toolboxLayout->addWidget(fellowshipLineWidget, 1, 0);
    toolboxLayout->addWidget(compositionLineWidget, 0, 1);
    toolboxLayout->addWidget(generalisationLineWidget, 1, 1);
    toolboxLayout->addWidget(classShapeWidget, 2, 0);

    toolboxItems->setLayout(toolboxLayout);
    toolboxItems->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum));
    toolBox->addItem(toolboxItems, "Prvky třídního diagramu");

}