#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QTextStream>
#include <QFileDialog>
#include <QStandardPaths>
#include <QFileInfo>
#include <QFile>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    curTree = ui->renderArea->getWorkingTree();
    connect(ui->deleteButton, SIGNAL(clicked()), this, SLOT(deleteClicked()));
    connect(ui->insertButton, SIGNAL(clicked()), this, SLOT(insertClicked()));

    // Create default save directory
    QString directory = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/TreeVisualizer";
    if (!QDir(directory).exists())
        QDir().mkdir(directory);

    ui->scrollAreaWidgetContents_3
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::insertClicked() const
{

    QString value = ui->insertTxtBox->text();
    int val = value.toInt();

    if(!this->curTree->insert(val))
        this->ui->statusBar->showMessage("Value " + QString::number(val) + " already exists in tree.");
     else
        this->ui->statusBar->showMessage("Value " + QString::number(val) + " inserted.");

    ui->renderArea->repaint();
    ui->insertTxtBox->setText("");
}

void MainWindow::deleteClicked() const
{
    QString value = ui->deleteTxtBox->text();
    int val = value.toInt();

    if(!this->curTree->deleteItem(value.toInt()))
        this->ui->statusBar->showMessage("Value " + QString::number(val) + " is not in tree...");
    else
        this->ui->statusBar->showMessage("Value " + QString::number(val) + " deleted.");

    ui->renderArea->repaint();
    ui->deleteTxtBox->setText("");
}

void MainWindow::SaveMenuClicked() const
{
    QString fileName = QFileDialog::getSaveFileName(const_cast<MainWindow*>(this), tr("Save File"),
                                 QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/TreeVisualizer",
                                 tr("Text files (*.txt);;Images (*.png *.jpg)"));

    if (QFileInfo(fileName).suffix() == "txt")
    {
        BSTreeMemento* state = curTree->createMemento();
        QString text = state->getTraversal();


        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            ui->statusBar->showMessage("Unable to open file at" + fileName);
            return;
        }

        state->writeToFile(file);
        ui->statusBar->showMessage("Tree was successfully saved to " + fileName);
    }

    // if not txt, save as image
    else if(!ui->renderArea->grab().save(fileName))
    {
        ui->statusBar->showMessage("Error: image was not saved!");
    }
    else{
        ui->statusBar->showMessage("Image was successfully saved.");
    }
}
