#include "ui.h"
#include "repo.h"
#include "service.h"

int main() {
    run_test_service();
    run_test_domain();
    run_test_repo();
    DynamicRepo* repository = createDynamicRepo();
    Service s = createService(repository);
    Ui ui = createUi(&s);
    start(&ui);
    destroyUi(&ui);
    return 0;
}
