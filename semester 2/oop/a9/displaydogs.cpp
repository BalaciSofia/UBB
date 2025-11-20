#include "displaydogs.h"
#include "ui_displaydogs.h"

displaydogs::displaydogs(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::displaydogs)
{
    ui->setupUi(this);
}

displaydogs::~displaydogs()
{
    delete ui;
}
