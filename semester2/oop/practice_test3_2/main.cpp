#include <QApplication>
#include <QPushButton>

#include "repository.h"
#include "service.h"
#include "mainwindow.h"
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    repository r("triangles.txt");
    service s(r);
    mainwindow w(nullptr, s);
    w.show();
    return a.exec();
}
