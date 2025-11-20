//
// Created by balac on 6/17/2025.
//

#ifndef ASTRONOMERWINDOW_H
#define ASTRONOMERWINDOW_H

#include <QWidget>

#include "Astronomer.h"
#include "Service.h"
#include "tablemodel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class AstronomerWindow; }
QT_END_NAMESPACE

class AstronomerWindow : public QWidget {
Q_OBJECT
private:
    Astronomer astronomer;
    Service& service;
    tablemodel* model;
    Ui::AstronomerWindow *ui;

public:
    explicit AstronomerWindow(Astronomer astronomer,Service &service,tablemodel *model, QWidget *parent = nullptr);
    ~AstronomerWindow() override;

};


#endif //ASTRONOMERWINDOW_H
