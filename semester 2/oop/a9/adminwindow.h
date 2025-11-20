#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QDialog>
#include "repo.h"
#include "controller_admin.h"

namespace Ui {
class adminwindow;
}

class adminwindow : public QDialog
{
    Q_OBJECT

public:
    explicit adminwindow(Controller_admin &controller_admin,QWidget *parent = nullptr);
    ~adminwindow();
    void populateTable();

private:
    Ui::adminwindow *ui;
    Controller_admin &controller_admin;

private slots:
    void on_addButton_clicked();
    void on_removeButton_clicked();
    void on_updateButton_clicked();
};


#endif // ADMINWINDOW_H
