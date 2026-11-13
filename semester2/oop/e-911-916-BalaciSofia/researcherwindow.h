//
// Created by balac on 6/17/2025.
//

#ifndef RESEARCHERWINDOW_H
#define RESEARCHERWINDOW_H

#include <QWidget>

#include "Observer.h"
#include "Service.h"

class Service;
QT_BEGIN_NAMESPACE
namespace Ui { class ResearcherWindow; }
QT_END_NAMESPACE

class ResearcherWindow : public QWidget ,public Observer{
Q_OBJECT

public:
    explicit ResearcherWindow(Service &service,Researcher researcher,QWidget *parent = nullptr);
    ~ResearcherWindow() override;
    void update()override;
private slots:
    void onAddButton();
    void onAcceptButton();
    void onSaveButton();
    void onDevelopButton();

private:
    Ui::ResearcherWindow *ui;
    Service &service;
    Researcher researcher;
};


#endif //RESEARCHERWINDOW_H
