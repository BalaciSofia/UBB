#include <QApplication>
#include <QPushButton>

#include "departments.h"
#include "departmentwindow.h"
#include "Repository.h"
#include "Service.h"
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Repository repository("departments.txt", "volunteers.txt");
    Service service(repository);

    for (auto &department : service.get_departments_service()) {
        DepartmentWindow * window = new DepartmentWindow(service,department);
        service.addObserver(std::shared_ptr<Observer>(window));
        window->show();
    }

    departments *w = new departments(service);
    service.addObserver(std::shared_ptr<Observer>(w));
    w->show();
    return a.exec();
}
