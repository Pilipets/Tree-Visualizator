#include "propertieswindow.h"

PropertiesWindow::PropertiesWindow(QWidget *parent) : QMainWindow(parent)
{
    this->setWindowTitle("Tree Properties");
    this->setFixedSize(QSize(400, 400));

    labelLayout = new QVBoxLayout;\
    typeLabel = new QLabel("Tree Type:");
    typeLabel->setStyleSheet("font-size: 14px;");
    labelLayout->addWidget(typeLabel);
    textAreaLayout = new QVBoxLayout;
    typeValue = new QLineEdit("");
    typeValue->setReadOnly(true);
    typeValue->setStyleSheet("color: black; width: 100px;"
                               "font-size: 14px;");
    textAreaLayout->addWidget(typeValue);

    containerLayout = new QHBoxLayout;
    containerLayout->addLayout(labelLayout);
    containerLayout->addLayout(textAreaLayout);

    preOrderTraversal = new QTextEdit;
    inOrderTraversal = new QTextEdit;
    postOrderTraversal = new QTextEdit;

    preOrderTraversal->setReadOnly(true);
    inOrderTraversal->setReadOnly(true);
    postOrderTraversal->setReadOnly(true);

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
    delete labelLayout;
    delete typeLabel;
    delete typeValue;
    delete textAreaLayout;

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

    this->typeValue->setText(info.type);
    this->preOrderTraversal->setText(info.preOrderTraversal);
    this->inOrderTraversal->setText(info.inOrderTraversal);
    this->postOrderTraversal->setText(info.postOrderTraversal);
}
