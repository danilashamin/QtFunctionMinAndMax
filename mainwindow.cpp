#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->btnLoadFile, SIGNAL(clicked(bool)), this, SLOT(loadFile()));
    connect(ui->btnCalculate, SIGNAL(clicked(bool)), this, SLOT(calculate()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadFile()
{
    QFileDialog fileOpenDialog;
    QString fileURI =fileOpenDialog.getOpenFileName(0, "Open input file","","*.txt");

    if(!QFile::exists(fileURI)) {
        showErrorDialog("File not selected, or does not exist.");
        return;
    }
    inputFile.setFileName(fileURI);
    QTextStream in(&inputFile);
    if(in.atEnd()) {
        showErrorDialog("File is empty.");
        return;
    }
}

void MainWindow::calculate()
{

}

void MainWindow::showErrorDialog(QString message)
{
    QErrorMessage errorDialog;
    errorDialog.showMessage(message);
    errorDialog.exec();
}
