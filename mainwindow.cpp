#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QFileDialog"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionOpen_json_file_with_inputs_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
    tr("Open Image"), "D:/Projects/january2022_test", tr("Image Files (*.json)"));
}

