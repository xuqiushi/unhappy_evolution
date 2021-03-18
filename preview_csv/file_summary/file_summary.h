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
#include <QProgressBar>
#include <QTimer>
#include <thread>
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
    QString file_path_;  // 文件路径
    QVBoxLayout *main_layout_;  // 主布局为垂直布局
    QHBoxLayout *parse_option_layout_;  // 第一行用来保存解析选项的为水平布局
    QGridLayout *main_content_layout_;  // 显示文件的各种信息的为一个grid布局
    preview_csv::ParseOption *parse_option_;  // 用来保存解析选项的
    QPushButton *start_parse_button_;  // 开始解析按钮
    FileInfo *file_info_;  // 文件基本信息保存
    QList<QStringList> table_lines_;  // 读取到的表格数据，双层list
    int row_count_;  // 读取到的表格行数
    int column_count_;  // 读取到的表格列数
    QList<QString> column_names_;  // 读取到的表格列名
    std::unordered_map<QString, int> column_unique_count_;  // 读取到的每一列的不重复值数量
    std::unordered_map<QString, std::unordered_set<QString>> column_unique_values_;  // 读取到的每一列的不重复值
    int current_progress_value_;  // 当前的解析进度
    bool current_progress_status_;  // 当前是否可以开始解析
    int actual_end_line_;  // 真实的结束行数，这个是为了修正进度条的总长度。解析开始的时候使用的结束行数为输入行数，未必是能读取到的最后行数
    QProgressBar *progress_bar_;  // 进度条
    QTimer *progress_timer_;  // 轮询用计时器
    std::thread back_ground_;  // 子线程，用来读取文件进行解析

  private:
    // 一行中插入两个属性，每个属性由一个标签和一个输入框组成
    void insertDoubleToRow(int row_index, int item_index, const QString &label_text, const QString &content_text);
    // 一行中插入一个属性，包括一个标签和一个输入框
    void insertSingleToRow(int row_index, const QString &label_text, const QString &content_text);
    // 一行中插入一个属性，包括一个标签和两个输入框
    void insertSingleToRow(int row_index,
                           const QString &label_text,
                           const QString &first_content_text,
                           const QString &second_content_text);
    // 获取文件基本信息
    void getFileInfo();
    // 提取所选范围内的表格信息
    void extractTableLines(
        int start_line,
        int end_line,
        const QString &line_sep);
    // 清除数据
    void clearData();

  public slots:
    void getParseOption(int start_line, int end_line, const QString &line_sep);  // 获取解析选项
    void receiveFilePath(QString file_path);  // 获取文件路径
    void setProgressValue();  // 设置解析进度
};
}

#endif //UNHAPPY_EVOLUTION_PREVIEW_CSV_FILE_SUMMARY_FILE_SUMMARY_H_
