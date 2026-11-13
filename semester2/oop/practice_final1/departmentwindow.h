//
// Created by balac on 6/15/2025.
//

#ifndef DEPARTMENTWINDOW_H
#define DEPARTMENTWINDOW_H

#include <QWidget>

#include "Observer.h"
#include "Service.h"


QT_BEGIN_NAMESPACE
namespace Ui { class DepartmentWindow; }
QT_END_NAMESPACE

class DepartmentWindow : public QWidget, public Observer{
Q_OBJECT

public:
    explicit DepartmentWindow(Service &service,Department department,QWidget *parent = nullptr);
    ~DepartmentWindow() override;
    void update() override;
private slots:
    void onAddButton();
    void onAssignButton();
private:
    Ui::DepartmentWindow *ui;
    Service &service;
    Department department;
};


#endif //DEPARTMENTWINDOW_H
