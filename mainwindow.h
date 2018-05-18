#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void loadFile();
    void calculate();

private:
    Ui::MainWindow *ui;
    void showErrorDialog(QString message);
    QFile inputFile;
};

#endif // MAINWINDOW_H
