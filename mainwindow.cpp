#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->btnLoadFile, SIGNAL(clicked(bool)), this, SLOT(loadFile()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadFile()
{
    QFileDialog fileOpenDialog;
    QString fileURI =fileOpenDialog.getOpenFileName(0, "Open input file","","*.txt");

    if(!QFile::exists(fileURI) && fileOpenDialog.closeEvent()) {
        showFileDontExistsDialog();
        return;
    }
    QFile inputFile(fileURI);
    QTextStream in(&inputFile);
    if(in.atEnd()) {
        showFileEmptyDialog();
        return;
    }
    while(!in.atEnd()) {

    }
}
void MainWindow::showFileDontExistsDialog(){
    QErrorMessage fileDontExistsDialog;
    fileDontExistsDialog.showMessage("File doesn't exist!");
    fileDontExistsDialog.exec();
}

void MainWindow::showFileEmptyDialog()
{
    QErrorMessage fileEmptyDialog;
    fileEmptyDialog.showMessage("File is empty.");
    fileEmptyDialog.exec();
}
