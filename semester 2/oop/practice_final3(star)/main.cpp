#include <iostream>
#include <QApplication>
#include <QPushButton>

#include "astronomerwindow.h"
#include "Repository.h"
#include "Service.h"
#include "tablemodel.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Repository repo("astronomers.txt", "stars.txt");
    Service service(repo);
    std::cout<<service.get_astronomers_service().size();
    tablemodel* model = new tablemodel(service);

    for (auto a : service.get_astronomers_service()) {
        AstronomerWindow* window = new AstronomerWindow(a, service, model);
        window->show();
    }

    return a.exec();
}