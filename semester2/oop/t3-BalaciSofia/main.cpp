#include <QApplication>
#include <QPushButton>

#include "mainwindow.h"
#include "repository.h"
#include "service.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    repository repo("documents.txt");
    service s(repo);
    mainwindow w(nullptr, s);
    w.show();
    return QApplication::exec();
}
