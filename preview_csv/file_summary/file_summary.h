//
// Created by 徐秋实 on 2021/3/9.
//

#ifndef UNHAPPY_EVOLUTION_PREVIEW_CSV_FILE_SUMMARY_FILE_SUMMARY_H_
#define UNHAPPY_EVOLUTION_PREVIEW_CSV_FILE_SUMMARY_FILE_SUMMARY_H_

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <unordered_map>
#include <unordered_set>
#include "preview_csv/parse_option/parse_option.h"

QT_BEGIN_NAMESPACE
namespace Ui { class FileSummary; }
QT_END_NAMESPACE

namespace preview_csv {

struct FileInfo {
    QString file_name;
    QString file_size;
};

class FileSummary : public QWidget {
  Q_OBJECT

  public:
    explicit FileSummary(QWidget *parent = nullptr);
    ~FileSummary() override;

  private:
    Ui::FileSummary *ui_;
    QString file_path_;
    QVBoxLayout *main_layout_;
    QHBoxLayout *parse_option_layout_;
    QGridLayout *main_content_layout_;
    preview_csv::ParseOption *parse_option_;
    QPushButton *start_parse_button_;
    FileInfo *file_info_;
    QList<QStringList> table_lines_;
    int row_count_;
    int column_count_;
    QList<QString> column_names_;
    std::unordered_map<QString, std::unordered_set<QString>> column_unique_values_;


  private:
    void insertDoubleToRow(int row_index, int item_index, const QString &label_text, const QString &content_text);
    void insertSingleToRow(int row_index, const QString &label_text, const QString &content_text);
    void getFileInfo(int start_line, int end_line, const QString &line_sep);
    void extractTableLines(
        int start_line,
        int end_line,
        const QString &line_sep);

  public slots:
    void getParseOption(int start_line, int end_line, const QString &line_sep);
    void receiveFilePath(QString file_path);
};
}

#endif //UNHAPPY_EVOLUTION_PREVIEW_CSV_FILE_SUMMARY_FILE_SUMMARY_H_
