#include <QApplication>
#include <QPushButton>

#include "mainwindow.h"
#include "repository.h"
#include "service.h"
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    repository r("equations.txt");
    service s(r);
    mainwindow w(nullptr, s);
    w.show();
    return a.exec();
}
