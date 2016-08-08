#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include "pcars/pcarsworker.h"
#include "clientData.h"
#include "dashboard/dashboard.h"
#include "dashboard/dashboardthread.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT


private:
    void refreshComPortList();


    QThread *gameThread;
    DashboardThread *dashboardThread;

    Dashboard *dashboard;

    PcarsWorker *pworker;



    clientDataStruct clientData;


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();



private slots:

    void on_pushButton_connectGame_clicked();
    void on_pushButton_clientDemo_clicked();
    void dashboardDemoClosed();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
