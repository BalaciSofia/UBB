//
// Created by balac on 6/17/2025.
//

#ifndef DEVLOPWINDOW_H
#define DEVLOPWINDOW_H

#include <QWidget>

#include "Service.h"
#include "Idea.h"

QT_BEGIN_NAMESPACE
namespace Ui { class devlopwindow; }
QT_END_NAMESPACE

class devlopwindow : public QWidget {
Q_OBJECT

public:
    explicit devlopwindow(Service &service,Idea &i,QWidget *parent = nullptr);
    ~devlopwindow() override;

private:
    Service &service;
    Idea& i;
    Ui::devlopwindow *ui;
};


#endif //DEVLOPWINDOW_H
