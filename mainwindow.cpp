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
    if (!inputFile.open(QIODevice::ReadOnly | QIODevice::Text)){
        showErrorDialog("Can't open file");
        return;
    }

    if(inputFile.atEnd()) {
        showErrorDialog("File is empty.");
        return;
    }
}

void MainWindow::calculate()
{
    if(!inputFile.isOpen()){
        showErrorDialog("Please, select file.");
        return;
    }
    if (ui->etIntervalFrom->toPlainText().isEmpty()||ui->etIntervalTo->toPlainText().isEmpty()) {
        showErrorDialog("Enter an interval.");
        return;
    }
    ui->etMin->setText("");
    ui->etMax->setText("");

    xIntervalFrom = ui->etIntervalFrom->toPlainText().toDouble();
    xIntervalTo =ui->etIntervalTo->toPlainText().toDouble();
    createPoints();

    ui->plot->clearGraphs();
    ui->plot->addGraph();
    ui->plot->graph(0)->setData(x, y);

    ui->plot->xAxis->setLabel("X");
    ui->plot->yAxis->setLabel("Y");

    double yMin, yMax;
    findMinAndMax(yMin, yMax);

    ui->plot->xAxis->setRange(xIntervalFrom, xIntervalTo);
    ui->plot->yAxis->setRange(yMin, yMax);
    ui->plot->replot();

    x.clear();
    y.clear();
}

void MainWindow::showErrorDialog(QString message)
{
    QErrorMessage errorDialog;
    errorDialog.showMessage(message);
    errorDialog.exec();
}

void MainWindow::findMinAndMax(double &min, double &max)
{
   min = y[0], max = y[0];
   double xMin = x[0], xMax = x[0];
   for (int i = 0; i < y.size(); i++){
       if(y[i]<=min) {
           min = y[i];
           xMin = x[i];
       }
       if(y[i]>=max) {
           max = y[i];
           xMax = x[i];
       }
       ui->etMin->setText("("+ QString::number(xMin)+"; "+QString::number(min)+")");
       ui->etMax->setText("("+QString::number(xMax)+"; "+QString::number(max)+")");
   }
}

void MainWindow::createPoints()
{
    QTextStream in(&inputFile);
    while(!in.atEnd()){
       createPointFromString(in.readLine());
    }
    in.flush();
    in.seek(0);
}

void MainWindow::createPointFromString(QString string)
{
    QStringList numbers = string.split(" ");
    double x = numbers[0].toDouble();
    double y = numbers[1].toDouble();

    if(x>=xIntervalFrom && x<=xIntervalTo) {
        this->x.append(x);
        this->y.append(y);
    }
}

void MainWindow::closeEvent(QCloseEvent *event) {
    inputFile.close();
}

