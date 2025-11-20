#include <iostream>
#include <QApplication>
#include <QPushButton>

#include "Repository.h"
#include "Service.h"
#include "biologistwindow.h"
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    Repository repo("biologist.txt","bacteria.txt");
    Service service(repo);
    std::cout<<service.get_biologists_service().size()<<"\n";
    std::cout<<service.get_bacteriums_service().size()<<"\n";

    for (auto &biologist :service.get_biologists_service()) {
        BiologistWindow * window = new BiologistWindow(service, biologist);
        service.addObserver(std::shared_ptr<Observer>(window));
        window->show();
    }
    return a.exec();
}
