#ifndef UPDATEDIALOG_H
#define UPDATEDIALOG_H

#include <QDialog>
#include "controller_admin.h"
namespace Ui {
class updatedialog;
}

class updatedialog : public QDialog
{
    Q_OBJECT

public:
    explicit updatedialog(Controller_admin &controller_admin,QWidget *parent = nullptr);
    ~updatedialog();
private slots:
    void onUpdateClicked();
private:
    Ui::updatedialog *ui;
    Controller_admin &controller_admin;
};

#endif // UPDATEDIALOG_H
