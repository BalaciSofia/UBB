#include "char.h"
#include "ui_char.h"

chart ::chart(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::chart)
{
    ui->setupUi(this);
}

chart ::~chart()
{
    delete ui;
}
