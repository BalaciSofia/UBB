#ifndef USERWINDOW_H
#define USERWINDOW_H

#include <QWidget>
#include "controller_admin.h"
#include "controller_user.h"

namespace Ui {
class userwindow;
}

class userwindow : public QWidget
{
    Q_OBJECT

public:
    explicit userwindow(Controller_admin &controller_admin,Controller_user &controller_use,QWidget *parent = nullptr);
    ~userwindow();
private slots:
    void onDisplayDogsClicked();
    void Display(std::vector<Dog> dogs);
    void onAdoptionListClicked();
    void onChartClicked();

private:
    Ui::userwindow *ui;
    Controller_user &controller_user;
    Controller_admin &controller_admin;
};

#endif // USERWINDOW_H
