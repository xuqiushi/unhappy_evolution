//
// Created by 徐秋实 on 2021/3/5.
//

#ifndef UNHAPPY_EVOLUTION_PREVIEW_CSV_CUSTOM_CSV_MODEL_H_
#define UNHAPPY_EVOLUTION_PREVIEW_CSV_CUSTOM_CSV_MODEL_H_
#include <QAbstractTableModel>

namespace preview_csv {
class CustomCsvModel : public QAbstractTableModel {
  Q_OBJECT
  public:
    explicit CustomCsvModel(QObject *parent = nullptr);
    ~CustomCsvModel() override;

    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    void setRowCount(int count);
    void setColumnCount(int count);
    void setCsvData(int row_count, int column_count, QList<QStringList> csv_data);
    void clear();

  private:
    QList<QStringList> csv_data_;
    int row_count_;
    int column_count_;
};
}

#endif //UNHAPPY_EVOLUTION_PREVIEW_CSV_CUSTOM_CSV_MODEL_H_
