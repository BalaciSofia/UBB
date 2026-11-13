#include <QApplication>
#include <QPushButton>

#include "mainwindow.h"
#include "repo.h"
#include "service.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    repo r("bills.txt");
    service s(r);
    mainwindow w(nullptr,s);
    w.show();
    return a.exec();
}
