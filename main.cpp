#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setObjectName("Im Main Window");
    w.show();
    return a.exec();
}
