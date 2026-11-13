
#include "controller.h"
#include "Ui.h"

int main() {
    Controller c;
    Ui ui(c);
    c.testadd();
    c.testsort();
    ui.start();
}
