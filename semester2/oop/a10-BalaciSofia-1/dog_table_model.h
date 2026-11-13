//
// Created by balac on 5/31/2025.
//

#ifndef DOG_TABLE_MODEL_H
#define DOG_TABLE_MODEL_H


#pragma once
#include <QAbstractTableModel>
#include "domain.h"
#include "controller_user.h"
class DogTableModel : public QAbstractTableModel {
    Q_OBJECT

private:
    Controller_user &s;
public:
    DogTableModel(Controller_user &s,QObject* parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;

};




#endif //DOG_TABLE_MODEL_H
