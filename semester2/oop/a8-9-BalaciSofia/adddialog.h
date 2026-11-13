#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QDialog>
#include "controller_admin.h"
namespace Ui {
class adddialog;
}

class adddialog : public QDialog
{
    Q_OBJECT

public:
    explicit adddialog(Controller_admin &controller_admin,QWidget *parent = nullptr);
    ~adddialog();

private:
    Ui::adddialog *ui;
    Controller_admin &controller_admin;
private slots:
    void onAddClicked();
};

#endif // ADDDIALOG_H
