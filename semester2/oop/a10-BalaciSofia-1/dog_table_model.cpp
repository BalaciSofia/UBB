//
// Created by balac on 5/31/2025.
//

#include "dog_table_model.h"
#include <QFont>

DogTableModel::DogTableModel(Controller_user &s,QObject* parent)
    : QAbstractTableModel{ parent },s{s}{
}

int DogTableModel::rowCount(const QModelIndex& parent) const {
    return this->s.get_adopted_dogs_controller().size();
}

int DogTableModel::columnCount(const QModelIndex& parent) const {
    return 4; // breed, name, age, photograph
}

QVariant DogTableModel::data(const QModelIndex& index, int role) const {
    Dog d = this->s.get_adopted_dogs_controller()[index.row()];
    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        switch (index.column()) {
            case 2: return QString::fromStdString(d.get_breed());
            case 0: return QString::fromStdString(d.get_name());
            case 1: return d.get_age();
            case 3: return QString::fromStdString(d.get_photograph());
            default: return QVariant();
        }
    }

    if (role == Qt::FontRole) {
        QFont font("Times", 12);
        font.setItalic(false);
        return font;
    }

    return QVariant();
}

QVariant DogTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section) {
            case 0: return QString("Name");
            case 1: return QString("Age");
            case 2: return QString("Breed");
            case 3: return QString("Photograph URL");
            default: break;
        }
    }
    return QVariant();
}

Qt::ItemFlags DogTableModel::flags(const QModelIndex& index) const {
    return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}


