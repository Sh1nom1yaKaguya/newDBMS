#include "mainwindow.h"

#include <QApplication>

// 简单的测试，第一次
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow   w;

    // w.show();
    return a.exec();
}
