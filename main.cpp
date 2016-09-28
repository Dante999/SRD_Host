#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;                       // Create MainWindow
    w.show();                           // Show MainWindow

    return a.exec();
}
