//
// Created by 徐秋实 on 2021/3/5.
//

#include <QDebug>
#include "custom_csv_model.h"

preview_csv::CustomCsvModel::CustomCsvModel(QObject *parent)
    : QAbstractTableModel(parent), row_count_(0), column_count_(0) {}

preview_csv::CustomCsvModel::~CustomCsvModel() {
    // 析构的时候删掉数据
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
    // 这里硬构造一个parent，不知道为什么一定要有parent，但是没办法，所以直接构造一个。
    QModelIndex parent = QModelIndex();
    this->setRowCount(row_count);
    this->setColumnCount(column_count);
    // 这里双重引用data防止复制
    this->csv_data_ = std::move(csv_data);
    // 调用父函数通知qt渲染
    this->beginInsertRows(parent, 0, this->row_count_ - 1);
    this->endInsertRows();
    this->beginInsertColumns(parent, 0, this->column_count_ - 1);
    this->endInsertColumns();
}

void preview_csv::CustomCsvModel::clear() {
    QModelIndex parent = QModelIndex();
    for (auto &string_list: this->csv_data_) {
        // 删除每行
        string_list.clear();
    }
    // 删除总体
    // 调用父函数，通知qt进行渲染
    this->csv_data_.clear();
    this->beginRemoveRows(parent, 0, this->row_count_ - 1);
    this->endRemoveRows();
    this->beginRemoveColumns(parent, 0, this->column_count_ - 1);
    this->endRemoveColumns();
}

QVariant preview_csv::CustomCsvModel::data(const QModelIndex &index, int role) const {
    // 不知道什么用，官网上这么写，所以直接复制过来。
    if (role != Qt::DisplayRole) {
        return QVariant();
    }
    // 如果传入的index的列在当前行长度范围内则返回值，否则返回空，以防止某些行解析的值个数与列数不一致报错。
    if (index.column() < this->csv_data_[index.row()].size()) {
        return this->csv_data_[index.row()][index.column()];
    } else {
        return QVariant();
    }
}