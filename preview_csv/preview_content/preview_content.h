//
// Created by 徐秋实 on 2021/3/9.
//

#ifndef UNHAPPY_EVOLUTION_PREVIEW_CSV_PREVIEW_CONTENT_PREVIEW_CONTENT_H_
#define UNHAPPY_EVOLUTION_PREVIEW_CSV_PREVIEW_CONTENT_PREVIEW_CONTENT_H_

#include <thread>
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTableView>
#include <QProgressBar>
#include <QTimer>
#include "preview_csv/data_model/custom_csv_model.h"

QT_BEGIN_NAMESPACE
namespace Ui { class PreviewContent; }
QT_END_NAMESPACE

namespace preview_csv {
class PreviewContent : public QWidget {
  Q_OBJECT

  public:
    explicit PreviewContent(QWidget *parent = nullptr);
    ~PreviewContent() override;

  private:
    Ui::PreviewContent *ui_;
    QVBoxLayout *preview_content_layout_;  // 整体layout
    QHBoxLayout *parse_option_layout_;  // 第一行layout
    preview_csv::ParseOption *parse_option_;  // 第一行
    QPushButton *start_parse_button_;  // 开始预览按钮
    QString file_path_;  // 文件路径
    QTableView *table_view_;  // 表格预览界面
    CustomCsvModel *table_data_;  // 表格数据
    QList<QStringList> csv_data_;  // 表格原始数据
    int row_count_; // 当前行数
    int column_count_;  // 当前列数
    int actual_end_line_;  // 当前范围的实际结束位置
    int current_progress_value_;  // 当前进度数字
    bool current_progress_status_;  // 当前任务状态
    QProgressBar *progress_bar_;  // 当前进度
    QTimer *progress_timer_;  // 轮询
    std::thread back_ground_;


  private:
    void setTableLines(const QString &file_path, int start_line, int end_line, const QString& line_sep);

  public slots:
    void getParseOption(int start_line, int end_line, const QString& line_sep);
    void receiveFilePath(QString file_path);
    void setProgressValue();
};
}


#endif //UNHAPPY_EVOLUTION_PREVIEW_CSV_PREVIEW_CONTENT_PREVIEW_CONTENT_H_
