//
// Created by balac on 5/29/2025.
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

#include "service.h"


QT_BEGIN_NAMESPACE
namespace Ui { class mainwindow; }
QT_END_NAMESPACE

class mainwindow : public QWidget {
Q_OBJECT
private:
    service &s;
public:
    mainwindow(QWidget *parent,service &s);
    ~mainwindow() override;

private:
    Ui::mainwindow *ui;
    void populateList();
private slots:
    void add();
};


#endif //MAINWINDOW_H
