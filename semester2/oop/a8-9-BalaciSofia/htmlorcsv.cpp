#include "htmlorcsv.h"
#include "ui_htmlorcsv.h"

htmlorcsv::htmlorcsv(QWidget *parent)
    : QDialog(parent)  // ✅ Call QDialog constructor
    , ui(new Ui::htmlorcsv)
{
    ui->setupUi(this);
}

htmlorcsv::~htmlorcsv()
{
    delete ui;
}

void htmlorcsv::on_htmlButton_clicked() {
    selectedChoice = "HTML";
    accept();  // ✅ Close dialog with success
}

void htmlorcsv::on_csvButton_clicked() {
    selectedChoice = "CSV";
    accept();
}

QString htmlorcsv::getChoice() const {
    return selectedChoice;
}
