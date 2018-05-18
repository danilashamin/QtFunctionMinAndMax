#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QVector>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void closeEvent(QCloseEvent *event);

private slots:
    void loadFile();
    void calculate();

private:
    Ui::MainWindow *ui;
    QFile inputFile;
    QVector<double> x, y;
    double xIntervalFrom, xIntervalTo;
    void showErrorDialog(QString message);
    void findMinAndMax(double &min, double &max);
    void createPoints();
    void createPointFromString(QString string);

};

#endif // MAINWINDOW_H
