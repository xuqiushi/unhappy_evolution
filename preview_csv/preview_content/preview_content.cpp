//
// Created by 徐秋实 on 2021/3/9.
//

// You may need to build the project (run Qt uic code generator) to get "ui_preview_content.h" resolved

#include <QDebug>
#include <QFile>
#include <tools/csv_line_parser.h>
#include <utility>
#include "preview_csv/parse_option/parse_option.h"
#include "preview_content.h"
#include "ui_preview_content.h"

preview_csv::PreviewContent::PreviewContent(QWidget *parent) :
    QWidget(parent),
    ui_(new Ui::PreviewContent),
    file_path_(QString("")),
    table_view_(new QTableView()),
    table_data_(new CustomCsvModel()),
    csv_data_(QList<QStringList>()),
    row_count_(0),
    column_count_(0),
    actual_end_line_(101),
    preview_content_layout_(new QVBoxLayout()),
    parse_option_layout_(new QHBoxLayout()),
    parse_option_(new preview_csv::ParseOption()),
    progress_bar_(new QProgressBar()),
    current_progress_status_(true),
    current_progress_value_(0),
    progress_timer_(new QTimer()) {
    ui_->setupUi(this);
    // 创建表格预览部分
    this->setLayout(this->preview_content_layout_);
    // 创建预览标签页
    this->table_view_->setModel(this->table_data_);
    // 表格内容-第一行控制解析选项
    // 水平放置解析选项与预览按钮
    this->parse_option_layout_->addWidget(this->parse_option_);
    this->start_parse_button_ = new QPushButton("预览");
    this->parse_option_layout_->addWidget(this->start_parse_button_);
    this->preview_content_layout_->addLayout(this->parse_option_layout_);
    this->preview_content_layout_->addWidget(this->progress_bar_);
    // 表格内容-最后放置预览界面
    this->preview_content_layout_->addWidget(this->table_view_, 9);
    // 点击按钮则发送预览信息选项
    connect(this->start_parse_button_,
            &QPushButton::pressed,
            this->parse_option_,
            &preview_csv::ParseOption::sendParseInfo);
    // 发送预览信息之后则显示表格
    connect(this->parse_option_,
            &preview_csv::ParseOption::sendInfo,
            this,
            &preview_csv::PreviewContent::getParseOption);
    connect(this->progress_timer_, &QTimer::timeout, this, &preview_csv::PreviewContent::setProgressValue);
//    connect(this, &preview_csv::PreviewContent::setProgressValue, this->progress_bar_, &QProgressBar::setValue);
}

preview_csv::PreviewContent::~PreviewContent() {
    delete ui_;
    delete preview_content_layout_;
}

void preview_csv::PreviewContent::setTableLines(const QString &file_path,
                                                int start_line,
                                                int end_line,
                                                const QString &line_sep) {
    // 纯读取文件函数，不能在这里处理model，否则会在子进程中与主进程抢占与model绑定的view
    QFile file(file_path);
    if (!file.open(QFile::ReadOnly |
        QFile::Text)) {
        qDebug() << " Could not open the file for reading";
        return;
    }
    QTextStream in(&file);

    QStringList line_string_list;
    int row_index = 0;
    int row_count = 0, column_count = 0;

    while (!in.atEnd() && row_index < end_line) {
        QString f_file_line = in.readLine();//读取文件的一行
        if (row_index < start_line && row_index != 0) {
            row_index++;
            continue;
        }
        line_string_list = tools::CsvLineParser(f_file_line, line_sep).getParsedList();
        this->csv_data_.append(line_string_list);
        row_count++;
        if (column_count < line_string_list.size()) {
            column_count = line_string_list.size();
        }
        row_index++;
//        emit this->setProgressValue(row_index);
        this->current_progress_value_ = row_index;
    }
    this->row_count_ = row_count;
    this->column_count_ = column_count;
    this->actual_end_line_ = start_line + row_count;
    file.close();//关闭文件

}

void preview_csv::PreviewContent::getParseOption(int start_line, int end_line, const QString &line_sep) {

    // 如果状态是true，即可以进行查询，则进入查询操作
    if (!this->file_path_.isEmpty() && this->current_progress_status_) {
        // 表示中止行
        this->actual_end_line_ = end_line;
        // 重置状态栏
        this->progress_bar_->reset();
        this->progress_bar_->setMinimum(start_line);
        this->progress_bar_->setMaximum(this->actual_end_line_);
        // 将状态标记为false，即不可查询
        this->current_progress_status_ = false;
        this->table_data_->clear();//清空
        for (auto &line: this->csv_data_) {
            line.clear();
        }
        this->csv_data_.clear();
        // 创建轮询timer
        this->progress_timer_->start(100);
        // 创建后台任务子进程。
        this->back_ground_ = std::thread(&preview_csv::PreviewContent::setTableLines, this, this->file_path_, start_line, end_line, line_sep);
    }
}

void preview_csv::PreviewContent::setProgressValue() {
    // 此为轮询任务，每次轮询会将当前的progress设置为读取到的值
    this->progress_bar_->setValue(this->current_progress_value_);
    this->progress_bar_->update();
    if (this->current_progress_value_ == this->actual_end_line_) {
        // 如果轮询时发现当前进度跟计算的总进度一致，那么停止任务并开始渲染。
        this->progress_bar_->setMaximum(this->actual_end_line_);
        this->back_ground_.join();
        this->table_data_->setCsvData(this->row_count_, this->column_count_,this->csv_data_);
        this->progress_timer_->stop();
        // 标记状态为可查询
        this->current_progress_status_ = true;
    }
}

void preview_csv::PreviewContent::receiveFilePath(QString file_path) {
    this->file_path_ = std::move(file_path);
    this->start_parse_button_->animateClick();
}
