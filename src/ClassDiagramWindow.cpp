/**
 * @file ClassDiagramWindow.cpp
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Jakub Dvořák (xdvora3q)
 */
#include <QPushButton>
#include <QResource>
#include <iostream>
#include "ClassDiagramWindow.h"
#include "ClassAttribute.h"

/**
 * ClassDiagramWindow::ClassDiagramWindow Initialiezes components and prepare all QWidgets and controls.
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
 * ClassDiagramWindow::initializeComponents Initializes components - creates a new instances of primary attributes.
 */
void ClassDiagramWindow::initializeComponents()
{
    classDiagramScene = new QGraphicsScene();
    classDiagramView = new QGraphicsView(classDiagramScene);

    taskBar = addToolBar("TaskBar");
    diagramTabs = new QToolBar();
    toolBox = new QToolBox;

    agregationToolItem = new QToolButton;
    associationToolItem = new QToolButton;
    compositionToolItem = new QToolButton;
    generalisationToolItem = new QToolButton;
    realizationToolItem = new QToolButton;
    directedAssociationToolItem = new QToolButton;
    classShapeToolItem     = new QToolButton;
    removeSelectedToolItem = new QToolButton;
}

/**
 * ClassDiagramWindow::setMainWindow Arranges controls in layout and sets window properties.
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
 * ClassDiagramWindow::setTaskBars Sets taskbar (task as open, save) and create a place for sequence diagrams.
 */
void ClassDiagramWindow::setTaskBars()
{
    taskBar->addAction("Open", this, &ClassDiagramWindow::openButtonClicked);
    taskBar->addAction("Save", this, &ClassDiagramWindow::saveButtonClicked);
    taskBar->addAction("Save as...", this, &ClassDiagramWindow::saveAsButtonClicked);
    taskBar->addAction("Undo", this, &ClassDiagramWindow::undoButtonClicked);
    taskBar->addAction("Redo", this, &ClassDiagramWindow::redoButtonClicked);


    diagramTabs->addWidget(prepareSequencDiagramTab("Třídní diagram"));
    diagramTabs->addWidget(prepareSequencDiagramTab("Sekvenční 1"));
    diagramTabs->addWidget(prepareSequencDiagramTab("Sekvenční 2"));
}

/**
 * ClassDiagramWindow::prepareToolItem Places buttons to a layout and creates a toolbar with the layout.
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
    toolboxItemLayout->setAlignment(newToolButton, Qt::AlignHCenter);
    toolboxItemLayout->setAlignment(label, Qt::AlignHCenter);

    QWidget* toolboxItem = new QWidget;
    toolboxItem->setLayout(toolboxItemLayout);
    //toolboxItem->setMaximumSize(toolboxItemSize, toolboxItemSize + label->size().height() + 20);
    return toolboxItem;
}

/**
 * ClassDiagramWindow::prepareSequencDiagramTab Creates a tabs for sequence diagrams.
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
 * ClassDiagramWindow::setTooBox Place all demanded Widgets into a toolar.
 */
void ClassDiagramWindow::setTooBox()
{
    toolBox->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Ignored));
    toolBox->setMinimumWidth(minToolboxWidth);
    QGroupBox *toolboxItems = new QGroupBox;
    QGridLayout *toolboxLayout = new QGridLayout;

    QWidget *agregationLineWidget = prepareToolItem(QIcon{":/agLine.png"}, "Agregation", agregationToolItem);
    QWidget *fellowshipLineWidget = prepareToolItem(QIcon{":/coLine.png"}, "Composition", compositionToolItem);
    QWidget *compositionLineWidget = prepareToolItem(QIcon{":/feLine.png"}, "Association", associationToolItem);
    QWidget *generalisationLineWidget = prepareToolItem(QIcon{":/geLine.png"}, "Generalization", generalisationToolItem);
    QWidget *realizationLineWidget = prepareToolItem(QIcon{":/realization.png"}, "Realization", realizationToolItem);
    QIcon aaa = QIcon{":/realization.png"};
    (void)aaa;
    QWidget *directedLineWidget = prepareToolItem(QIcon{":/directedAssociation.png"},
                                                  "Directed association", directedAssociationToolItem);
    QWidget *classShapeWidget = prepareToolItem(QIcon{":/classShape.png"}, "Class node", classShapeToolItem);
    QWidget *removeSelectedWidget = prepareToolItem(QIcon{":/closeCross.png"}, "Remove selected", removeSelectedToolItem);

    toolboxLayout->addWidget(agregationLineWidget, 0, 0);
    toolboxLayout->addWidget(fellowshipLineWidget, 1, 0);
    toolboxLayout->addWidget(compositionLineWidget, 0, 1);
    toolboxLayout->addWidget(generalisationLineWidget, 1, 1);
    toolboxLayout->addWidget(realizationLineWidget, 2, 0);
    toolboxLayout->addWidget(directedLineWidget, 2, 1);
    toolboxLayout->addWidget(classShapeWidget, 3, 0);
    toolboxLayout->addWidget(removeSelectedWidget, 3, 1);

    toolboxItems->setLayout(toolboxLayout);
    toolboxItems->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum));
    toolBox->addItem(toolboxItems, "Prvky třídního diagramu");

}

/**
 * ClassDiagramWindow::addClassNode Insert new claasNode into scene of class diagram Window.
 */
void ClassDiagramWindow::addClassNode()
{
    ClassNode *newOne = new ClassNode();
    newOne->setPos(0,0);
    classDiagramScene->addItem(newOne);
}

/**
 * ClassDiagramWindow::removeClassNode Removes all selected class nodes.
 */
void ClassDiagramWindow::removeClassNode()
{
    QList<QGraphicsItem *> selectedItems =  classDiagramScene->selectedItems();
    for (QGraphicsItem *item : selectedItems)
    {
        ClassNode *node = dynamic_cast<ClassNode *>(item);
        if(node)
        {
            QSet<Line *> connections = node->getConnections();
            for(Line * connection : connections)
                delete connection;

            classDiagramScene->removeItem(item);
            delete item;
        }
    }
}

/**
 * ClassDiagramWindow::connectComponents Connets all signals and slots
 */
void ClassDiagramWindow::connectComponents()
{
    connect(classShapeToolItem,  &QToolButton::pressed, this, &ClassDiagramWindow::addClassNode);
    connect(removeSelectedToolItem,  &QToolButton::pressed, this, &ClassDiagramWindow::removeClassNode);
    connect(associationToolItem, &QToolButton::pressed, this, &ClassDiagramWindow::associationSelected);
    
    connect(compositionToolItem, &QToolButton::pressed, this, &ClassDiagramWindow::compositionSelected);
    connect(agregationToolItem, &QToolButton::pressed, this, &ClassDiagramWindow::agregationSelected);
    connect(generalisationToolItem, &QToolButton::pressed, this, &ClassDiagramWindow::generalisationSelected);
    connect(directedAssociationToolItem, &QToolButton::pressed, this, &ClassDiagramWindow::directedAssociationSelected);
    connect(realizationToolItem, &QToolButton::pressed, this, &ClassDiagramWindow::realizationSelected);

    connect(classDiagramScene, &QGraphicsScene::selectionChanged, this, &ClassDiagramWindow::selectionChanged);

}

/**
 * ClassDiagramWindow::setAllNodesColor Sets border color to all nodes and to nodeColor
 * @param color new node color
 */
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

/**
 * To a newLine pointer creates line
 */
void ClassDiagramWindow::associationSelected()
{
    classDiagramScene->clearSelection();
    setAllNodesColor(realtionShipSelectedColor);
    newLine = new AssociationLine;
}

/**
 * To a newLine pointer creates composition line
 */
void ClassDiagramWindow::compositionSelected()
{
    classDiagramScene->clearSelection();
    setAllNodesColor(realtionShipSelectedColor);
    newLine = new CompositionLine;
}

/**
 * To a newLine pointer creates agregation line
 */
void ClassDiagramWindow::agregationSelected()
{
    classDiagramScene->clearSelection();
    setAllNodesColor(realtionShipSelectedColor);
    newLine = new AgregationLine();
}

/**
 * To a newLine pointer creates generalisation line
 */
void ClassDiagramWindow::generalisationSelected()
{
    classDiagramScene->clearSelection();
    setAllNodesColor(realtionShipSelectedColor);
    newLine = new GeneralizationLine();
}

/**
 * To a newLine pointer creates directed association line
 */
void ClassDiagramWindow::directedAssociationSelected()
{
    classDiagramScene->clearSelection();
    setAllNodesColor(realtionShipSelectedColor);
    newLine = new DirectedAssociationLine();
}

/**
 * To a newLine pointer creates realization line
 */
void ClassDiagramWindow::realizationSelected()
{
    classDiagramScene->clearSelection();
    setAllNodesColor(realtionShipSelectedColor);
    newLine = new RealizationLine();
}

/**
 * ClassDiagramWindow::selectionChanged When selection changes and a new relationship is invoked,
 * handle adding new relationship.
 */
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

/**
 * ClassDiagramWindow::getSelectedNode finds first selected node
 *
 * @return selected node
 */
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

/**
 * ClassDiagramWindow::connectNodes Connect two nodes by relationship
 */
void ClassDiagramWindow::connectNodes()
{
    newLine->initialize(firstToSelect, secondToSelect);
    classDiagramScene->addItem(newLine);
    firstToSelect->addLine(newLine);
    secondToSelect->addLine(newLine);

    firstToSelect = nullptr;
    secondToSelect = nullptr;
}

/**
 * Slot for handling click action on "Open" button
 */
void ClassDiagramWindow::openButtonClicked()
{
    std::cerr << "Clicked on \"Open\" button!\n";
}

/**
 * Slot for handling click action on "Save" button
 */
void ClassDiagramWindow::saveButtonClicked()
{
    std::cerr << "Clicked on \"Save\" button!\n";
}

/**
 * Slot for handling click action on "Save as..." button
 */
void ClassDiagramWindow::saveAsButtonClicked()
{
    std::cerr << "Clicked on \"Save as...\" button!\n";
}

/**
 * Slot for handling click action on "Undo" button
 */
void ClassDiagramWindow::undoButtonClicked()
{
    std::cerr << "Clicked on \"Undo\" button!\n";
}

/**
 * Slot for handling click action on "Redo" button
 */
void ClassDiagramWindow::redoButtonClicked()
{
    std::cerr << "Clicked on \"Redo\" button!\n";
}