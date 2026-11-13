#include <iostream>
#include <QApplication>
#include <QPushButton>

#include "Repository.h"
#include "Researcher.h"
#include "Service.h"
#include "researcherwindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Repository repo("researchers.txt","ideas.txt");
    Service service(repo);

    std::cout<<service.getResearchers_service().size()<<std::endl;
    for (auto &researcher : service.getResearchers_service()) {
        ResearcherWindow * window = new ResearcherWindow(service,researcher);
        service.addObserver(std::shared_ptr<Observer>(window));
        window->show();
    }
    return a.exec();
}
