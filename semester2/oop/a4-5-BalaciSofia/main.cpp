#include "controller_admin.h"
#include "repo.h"
#include "ui.h"
#include "test.h"
int main() {
    Test t;
    t.test_all();
    Repository repo;
    Controller_admin controller_admin(repo);
    Controller_user controller_user(repo);
    Ui ui(controller_admin,controller_user);
    ui.start();
    return 0;
}

