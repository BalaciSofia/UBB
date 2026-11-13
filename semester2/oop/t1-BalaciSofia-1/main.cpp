
#include "service.h"
#include "repo.h"
#include "ui.h"
int main() {
    Repository repo;
    Service service(repo);
    service.Test_addSchool_serv();
    std::cout<<"add school test passed\n";
    Ui ui(service);
    ui.start();
    return 0;
}
