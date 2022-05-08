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
#include "ClassAttribute.h"

/**
 * Initialiezes components and prepare all QWidgets and controls.
 */
ClassDiagramWindow::ClassDiagramWindow()
{
    initializeComponents();
    connectComponents();
    setTooBox();
    setTaskBars();
    setMainWindow();


    ///////////////TESTING//////////////
    Class newOne = Class{"Moje Třída", std::make_tuple(0,0)};
    ClassNode *node = new ClassNode(newOne);
    node->addAtribute(ClassAttribute{"atribut hej",AccessModifier::PRIVATE,"string"});
    node->addAtribute(ClassAttribute{"další atribut",AccessModifier::PROTECTED,"int"});
    std::vector<MethodParameter> par1{MethodParameter{"par1", "int"}, MethodParameter{"par2", "DateTime"}, MethodParameter{"long parameter3", "string"}};
    node->addMethod(ClassMethod{"Metoda 1",AccessModifier::PROTECTED, par1,"string"});
    node->addMethod(ClassMethod{"Metoda 2",AccessModifier::PACKAGE_PRIVATE, par1,"DateTime"});
    classDiagramScene->addItem(node);
}

/**
 * Initializes components - creates a new instances of primary attributes.
 */
void ClassDiagramWindow::initializeComponents()
{
    classDiagramScene = new QGraphicsScene();
    classDiagramView = new QGraphicsView(classDiagramScene);

    taskBar = addToolBar("TaskBar");
    diagramTabs = new QToolBar();
    toolBox = new QToolBox;

    agregationToolItem = new QToolButton;
    realizationToolItem = new QToolButton;
    compositionToolItem = new QToolButton;
    generalisationToolItem = new QToolButton;
    classShapeToolItem     = new QToolButton;
    removeSelectedToolItem = new QToolButton;
}

/**
 * Arranges controls in layout and sets window properties.
 */
void ClassDiagramWindow::setMainWindow()
{
    QGridLayout *windowLayout = new QGridLayout;
    QGridLayout *modellingLayout = new QGridLayout;

    modellingLayout->addWidget(toolBox,0,0);
    modellingLayout->addWidget(classDiagramView,0,1);

    QWidget *modellingSpace = new QWidget;
    modellingSpace->setLayout(modellingLayout);

    windowLayout->addWidget(modellingSpace,0,0);
    windowLayout->addWidget(diagramTabs,1,0);

    classDiagramCenterWidget = new QWidget;
    classDiagramCenterWidget->setLayout(windowLayout);

    setCentralWidget(classDiagramCenterWidget);
    this->setMinimumSize(800,600);
    this->setWindowTitle("UML Class Creator");
}

/**
 * Sets taskbar (task as open, save) and create a place for sequence diagrams.
 */
void ClassDiagramWindow::setTaskBars()
{
    taskBar->addAction("Open");
    taskBar->addAction("Save");
    taskBar->addAction("Save as...");
    taskBar->addAction("Undo");
    taskBar->addAction("Redo");


    diagramTabs->addWidget(prepareSequencDiagramTab("Třídní diagram"));
    diagramTabs->addWidget(prepareSequencDiagramTab("Sekvenční 1"));
    diagramTabs->addWidget(prepareSequencDiagramTab("Sekvenční 2"));
}

/**
 * Places buttons to a layout and creates a toolbar with the layout.
 *
 * @param icon Icon that should be placed in button.
 * @param labelString String that will be under the icon.
 * @return QWidget representing a toolbar.
 */
QWidget *ClassDiagramWindow::prepareToolItem(QIcon icon, QString labelString, QToolButton *newToolButton)
{
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

/**
 * Creates a tabs for sequence diagrams.
 *
 * @param label QString of text which will be written on a tab.
 * @return QWidget representig a diagram tab manager.
 */
QWidget *ClassDiagramWindow::prepareSequencDiagramTab(QString label)
{
    static QIcon icon = QIcon(":/closeCross.png");
    QWidget *newTab = new QWidget;
    QPushButton *picture = new QPushButton(icon,"");

    QGridLayout *actionLayout = new QGridLayout();
    actionLayout->addWidget(new QPushButton(label),0,0);
    actionLayout->addWidget(picture,0,1);
    newTab->setLayout(actionLayout);

    return newTab;
}

/**
 * Place all demanded Widgets into a toolar.
 */
void ClassDiagramWindow::setTooBox()
{
    toolBox->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Ignored));
    toolBox->setMinimumWidth(minToolboxWidth);
    QGroupBox *toolboxItems = new QGroupBox;
    QGridLayout *toolboxLayout = new QGridLayout;

    QWidget *agregationLineWidget = prepareToolItem(QIcon{":/agLine.png"}, "Agregation", agregationToolItem);
    QWidget *fellowshipLineWidget = prepareToolItem(QIcon{":/coLine.png"}, "Composition", compositionToolItem);
    QWidget *compositionLineWidget = prepareToolItem(QIcon{":/feLine.png"}, "Realization", realizationToolItem);
    QWidget *generalisationLineWidget = prepareToolItem(QIcon{":/geLine.png"}, "Generalization", generalisationToolItem);
    QWidget *classShapeWidget = prepareToolItem(QIcon{":/classShape.png"}, "Class node", classShapeToolItem);
    QWidget *removeSelectedWidget = prepareToolItem(QIcon{":/closeCross.png"}, "Remove selected", removeSelectedToolItem);

    toolboxLayout->addWidget(agregationLineWidget, 0, 0);
    toolboxLayout->addWidget(fellowshipLineWidget, 1, 0);
    toolboxLayout->addWidget(compositionLineWidget, 0, 1);
    toolboxLayout->addWidget(generalisationLineWidget, 1, 1);
    toolboxLayout->addWidget(classShapeWidget, 2, 0);
    toolboxLayout->addWidget(removeSelectedWidget, 2, 1);

    toolboxItems->setLayout(toolboxLayout);
    toolboxItems->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum));
    toolBox->addItem(toolboxItems, "Prvky třídního diagramu");

}

/**
 * Insert new claasNode into scene of class diagram Window.
 */
void ClassDiagramWindow::addClassNode()
{
    ClassNode *newOne = new ClassNode();
    newOne->setPos(0,0);
    classDiagramScene->addItem(newOne);
}

void ClassDiagramWindow::removeClassNode()
{
    QList<QGraphicsItem *> selectedItems =  classDiagramScene->selectedItems();
    for (QGraphicsItem *item : selectedItems)
        classDiagramScene->removeItem(item);
    qDeleteAll(selectedItems);
}

void ClassDiagramWindow::connectComponents()
{
    connect(classShapeToolItem,  &QToolButton::pressed, this, &ClassDiagramWindow::addClassNode);
    connect(removeSelectedToolItem,  &QToolButton::pressed, this, &ClassDiagramWindow::removeClassNode);
    connect(realizationToolItem, &QToolButton::pressed, this, &ClassDiagramWindow::relationShipSelected);
    connect(classDiagramScene, &QGraphicsScene::selectionChanged, this, &ClassDiagramWindow::selectionChanged);
}

void ClassDiagramWindow::setAllNodesColor(QColor color)
{
    nodeColor = color;
    QList<QGraphicsItem *> allNodes = classDiagramScene->items();
    for(QGraphicsItem *maybeNode : allNodes)
    {
        ClassNode *definetlyNode = dynamic_cast<ClassNode *>(maybeNode);
        if(definetlyNode)
            definetlyNode->setBorderColor(nodeColor);

    }
}

void ClassDiagramWindow::relationShipSelected()
{
    classDiagramScene->clearSelection();
    setAllNodesColor(realtionShipSelectedColor);
}

void ClassDiagramWindow::selectionChanged()
{
    if (nodeColor == Qt::black)
        return;
    if(nodeColor == realtionShipSelectedColor && firstToSelect == nullptr)
    {
        firstToSelect = getSelectedNode();
        if(firstToSelect)
            firstToSelect->setBorderColor(nodeFirstSelectedColor);
        classDiagramScene->clearSelection();
    }
    else if(nodeColor == realtionShipSelectedColor && firstToSelect != nullptr) //first node selected and still in selctionMode
    {
        secondToSelect = getSelectedNode();
        if(secondToSelect && secondToSelect != firstToSelect)
        {
            setAllNodesColor(nodeNormalColor);
            classDiagramScene->clearSelection();
            connectNodes();
        }
    }
}

ClassNode *ClassDiagramWindow::getSelectedNode()
{
    ClassNode *toReturn;
    QList<QGraphicsItem *> selectedNodes = classDiagramScene->selectedItems();
    if(selectedNodes.count() > 1)
    {
        for(QGraphicsItem *node : selectedNodes)
        {
            toReturn = dynamic_cast<ClassNode*>(node);
            if(toReturn)
                return toReturn;
        }
    }
    else if (selectedNodes.count() == 1)
        return dynamic_cast<ClassNode *>(selectedNodes[0]);
    return nullptr;
}

void ClassDiagramWindow::connectNodes()
{
    Line *newLine = new Line(firstToSelect,secondToSelect);
    classDiagramScene->addItem(newLine);
    firstToSelect->addLine(newLine);
    secondToSelect->addLine(newLine);

    firstToSelect = nullptr;
    secondToSelect = nullptr;

}
