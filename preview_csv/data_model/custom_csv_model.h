//
// Created by 徐秋实 on 2021/3/5.
//

#ifndef UNHAPPY_EVOLUTION_PREVIEW_CSV_DATA_MODEL_CUSTOM_CSV_MODEL_H_
#define UNHAPPY_EVOLUTION_PREVIEW_CSV_DATA_MODEL_CUSTOM_CSV_MODEL_H_
#include <QAbstractTableModel>

namespace preview_csv {
class CustomCsvModel : public QAbstractTableModel {
  Q_OBJECT
  public:
    explicit CustomCsvModel(QObject *parent = nullptr);
    ~CustomCsvModel() override;

    [[nodiscard]] int rowCount(const QModelIndex &parent) const override;  // 继承于abs，返回表格行数
    [[nodiscard]] int columnCount(const QModelIndex &parent) const override;  // 继承于abs，返回表格列数
    [[nodiscard]] QVariant data(const QModelIndex &index, int role) const override;  // 继承于abs，返回表格某个cell值，包含渲染方式
    void setRowCount(int count);  // 设置行数
    void setColumnCount(int count);  // 设置列数
    void setCsvData(int row_count, int column_count, QList<QStringList> csv_data);  // 设置数据
    void clear();  // 删除所有数据

  private:
    QList<QStringList> csv_data_;  // 保存数据为双层list结构，即二维表，每个值为字符串
    int row_count_;  // 保存行数
    int column_count_;  // 保存列数
};
}

#endif //UNHAPPY_EVOLUTION_PREVIEW_CSV_DATA_MODEL_CUSTOM_CSV_MODEL_H_
