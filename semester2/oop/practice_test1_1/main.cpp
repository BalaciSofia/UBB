

#include "repo.h"
#include "service.h"
#include "ui.h"

int main() {
    Repository repo=Repository();
    repo.test_add_station_repo();
     Service service=Service(repo);
     service.test_add_station_serv();
     Ui ui=Ui(service);
     ui.start();
    return 0;
}
