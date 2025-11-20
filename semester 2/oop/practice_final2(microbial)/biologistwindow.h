//
// Created by balac on 6/16/2025.
//

#ifndef BIOLOGISTWINDOW_H
#define BIOLOGISTWINDOW_H

#include <QWidget>
#include "observer.h"
#include "service.h"
#include "biologist.h"
QT_BEGIN_NAMESPACE
namespace Ui { class BiologistWindow; }
QT_END_NAMESPACE

class BiologistWindow : public QWidget,public Observer {
Q_OBJECT

public:
    explicit BiologistWindow(Service &service,Biologist biologist,QWidget *parent = nullptr);
    ~BiologistWindow() override;
    void update() override;
private slots:
    void onComboBoxSelectionChanged(int index);
    void onAddButtonClicked();
private:
    Ui::BiologistWindow *ui;
    Service &service;
    Biologist biologist;
};


#endif //BIOLOGISTWINDOW_H
