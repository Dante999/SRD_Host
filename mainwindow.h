#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include "pcars/pcarsworker.h"
#include "clientData.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT


private:
    void refreshComPortList();


    QThread *workerThread;
    PcarsWorker *pworker;

    struct_client clientData;


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();



private slots:


    void on_pushButton_connectGame_clicked();

    void on_pushButton_clientDemo_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
