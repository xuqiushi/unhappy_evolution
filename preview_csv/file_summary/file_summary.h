//
// Created by 徐秋实 on 2021/3/9.
//

#ifndef UNHAPPY_EVOLUTION_PREVIEW_CSV_FILE_SUMMARY_FILE_SUMMARY_H_
#define UNHAPPY_EVOLUTION_PREVIEW_CSV_FILE_SUMMARY_FILE_SUMMARY_H_

#include <QWidget>
#include <QGridLayout>

QT_BEGIN_NAMESPACE
namespace Ui { class FileSummary; }
QT_END_NAMESPACE

namespace preview_csv {
class FileSummary : public QWidget {
  Q_OBJECT

  public:
    explicit FileSummary(QWidget *parent = nullptr);
    ~FileSummary() override;

  private:
    Ui::FileSummary *ui_;
    QGridLayout *main_layout_;

  private:
    void insertDoubleToRow(int row_index, int item_index, const QString& label_text, const QString& content_text);
    void insertSingleToRow(int row_index, const QString& label_text, const QString& content_text);
};
}

#endif //UNHAPPY_EVOLUTION_PREVIEW_CSV_FILE_SUMMARY_FILE_SUMMARY_H_
