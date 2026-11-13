//
// Created by balac on 6/15/2025.
//

#ifndef DEPARTMENTS_H
#define DEPARTMENTS_H

#include <QWidget>

#include "Observer.h"


class Service;
QT_BEGIN_NAMESPACE
namespace Ui { class departments; }
QT_END_NAMESPACE

class departments : public QWidget,public Observer {
Q_OBJECT

public:
    explicit departments(Service &service,QWidget *parent = nullptr);
    ~departments() override;
    void update() override;
private:
    Ui::departments *ui;
    Service &service;
};


#endif //DEPARTMENTS_H
