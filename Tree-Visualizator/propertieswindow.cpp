#include "propertieswindow.h"

PropertiesWindow::PropertiesWindow(QWidget *parent) : QMainWindow(parent)
{
    this->setWindowTitle("Tree Properties");
    this->setFixedSize(QSize(400, 400));

    containerLayout = new QHBoxLayout;

    preOrderTraversal = new QTextEdit;
    inOrderTraversal = new QTextEdit;
    postOrderTraversal = new QTextEdit;

    preOrderTraversal->setReadOnly(true);
    inOrderTraversal->setReadOnly(true);
    postOrderTraversal->setReadOnly(true);

    // Create the main layout and add all the widgets to it
    mainLayout = new QVBoxLayout;
    mainLayout->addLayout(containerLayout);
    mainLayout->addWidget(new QLabel("Preorder Traversal:"));
    mainLayout->addWidget(preOrderTraversal);
    mainLayout->addWidget(new QLabel("Inorder Traversal:"));
    mainLayout->addWidget(inOrderTraversal);
    mainLayout->addWidget(new QLabel("Postorder Traversal:"));
    mainLayout->addWidget(postOrderTraversal);

    centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);

    this->setCentralWidget(centralWidget);
}

PropertiesWindow::~PropertiesWindow()
{
    delete containerLayout;
    delete preOrderTraversal;
    delete inOrderTraversal;
    delete postOrderTraversal;
    delete mainLayout;
    delete centralWidget;
}

void PropertiesWindow::show()
{
    this->setVisible(true);
    this->activateWindow();
}

void PropertiesWindow::closeWindow()
{
    this->close();
}

void PropertiesWindow::update(Tree *tree)
{
    GetTraversal info;
    tree->accept(info);

    this->preOrderTraversal->setText(info.preOrderTraversal);
    this->inOrderTraversal->setText(info.inOrderTraversal);
    this->postOrderTraversal->setText(info.postOrderTraversal);
}
