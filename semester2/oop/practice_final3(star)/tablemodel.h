//
// Created by balac on 6/17/2025.
//


#ifndef TABLEMODEL_H
#define TABLEMODEL_H


#include <QAbstractTableModel>
#include <vector>
#include <QObject>
#include "Service.h"

class tablemodel : public QAbstractTableModel {
    Q_OBJECT

private:
    Service& service;

public:
    explicit tablemodel(Service& service, QObject* parent = nullptr)
        : QAbstractTableModel(parent), service(service) {}

    int rowCount(const QModelIndex& parent = QModelIndex()) const override {
        return service.get_stars_service().size();
    }

    int columnCount(const QModelIndex& parent = QModelIndex()) const override {
        return 5;
    }

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
        if(index.row() < 0 || index.row() >= rowCount()) return QVariant();
        if(index.column() < 0 || index.column() >= columnCount()) return QVariant();
        if(role == Qt::DisplayRole) {
            Star star = service.get_stars_service()[index.row()];
            switch(index.column()) {
                case(0):
                    return QVariant(QString::fromStdString(star.get_name()));
                case(1):
                    return QVariant(QString::fromStdString(star.get_constellation()));
                case(2):
                    return QVariant(QString::fromStdString(std::to_string(star.get_ra())));
                case(3):
                    return QVariant(QString::fromStdString(std::to_string(star.get_dec())));
                case(4):
                    return QVariant(QString::fromStdString(std::to_string(star.get_diameter())));
            }
        }
        return QVariant();
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override {
        if (role != Qt::DisplayRole || orientation != Qt::Horizontal) return QVariant();
        switch (section) {
            case 0: return "Name";
            case 1: return "Constellation";
            case 2: return "Ra";
            case 3: return "Dec";
            case 4: return "Diameter";
            default: return QVariant();
        }
    }

    void refresh() {
        beginResetModel();
        endResetModel();
    }
};




#endif //TABLEMODEL_H
