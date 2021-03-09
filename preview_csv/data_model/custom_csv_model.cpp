//
// Created by 徐秋实 on 2021/3/5.
//

#include <QDebug>
#include "custom_csv_model.h"

preview_csv::CustomCsvModel::CustomCsvModel(QObject *parent)
    : QAbstractTableModel(parent), row_count_(0), column_count_(0) {}

preview_csv::CustomCsvModel::~CustomCsvModel() {
    this->clear();
};

int preview_csv::CustomCsvModel::rowCount(const QModelIndex &parent) const {
    return this->row_count_;
}

int preview_csv::CustomCsvModel::columnCount(const QModelIndex &parent) const {
    return this->column_count_;
}

void preview_csv::CustomCsvModel::setRowCount(int count) {
    this->row_count_ = count;
}

void preview_csv::CustomCsvModel::setColumnCount(int count) {
    this->column_count_ = count;
}

void preview_csv::CustomCsvModel::setCsvData(int row_count, int column_count, QList<QStringList> csv_data) {
    QModelIndex parent = QModelIndex();
    this->setRowCount(row_count);
    this->setColumnCount(column_count);
    this->csv_data_ = std::move(csv_data);
    this->beginInsertRows(parent, 0, this->row_count_ - 1);
    this->endInsertRows();
    this->beginInsertColumns(parent, 0, this->column_count_ - 1);
    this->endInsertColumns();
}

void preview_csv::CustomCsvModel::clear() {
    QModelIndex parent = QModelIndex();
    for (auto &string_list: this->csv_data_) {
        string_list.clear();
    }
    this->csv_data_.clear();
    this->beginRemoveRows(parent, 0, this->row_count_ - 1);
    this->endRemoveRows();
    this->beginRemoveColumns(parent, 0, this->column_count_ - 1);
    this->endRemoveColumns();
}

QVariant preview_csv::CustomCsvModel::data(const QModelIndex &index, int role) const {
    if (role != Qt::DisplayRole) {
        return QVariant();
    }
    return this->csv_data_[index.row()][index.column()];
}