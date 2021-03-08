//
// Created by 徐秋实 on 2021/3/4.
//

#ifndef UNHAPPY_EVOLUTION_PREVIEW_CSV_MAIN_VIEW_H_
#define UNHAPPY_EVOLUTION_PREVIEW_CSV_MAIN_VIEW_H_

#include <QWidget>
#include <QTableView>
#include <QStandardItemModel>
#include "custom_csv_model.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainView; }
QT_END_NAMESPACE

namespace preview_csv {
class MainView : public QWidget {
  Q_OBJECT

  public:
    explicit MainView(QWidget *parent = nullptr);
    ~MainView() override;

  private slots:
    void getFileInfo(const QString &file_path);
    void getParseOption(int start_line, int end_line, const QString& line_sep);

  private:
    void setTableLines(const QString &file_path, int start_line, int end_line, const QString& line_sep);
    static QStringList parseCsv(const QString &string, const QString& line_sep);

  private:
    Ui::MainView *ui_;
    QTableView *table_view_;
    CustomCsvModel *table_data_;
    QString file_path_;
};
}

#endif //UNHAPPY_EVOLUTION_PREVIEW_CSV_MAIN_VIEW_H_
