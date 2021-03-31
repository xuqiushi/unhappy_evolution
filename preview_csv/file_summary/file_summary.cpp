//
// Created by 徐秋实 on 2021/3/9.
//

// You may need to build the project (run Qt uic code generator) to get "ui_file_summary.h" resolved

#include <QFile>
#include <QDir>
#include <QLabel>
#include <QTextEdit>
#include <QLineEdit>
#include <QDebug>
#include <tools/csv_line_parser.h>
#include "file_summary.h"
#include "ui_file_summary.h"

preview_csv::FileSummary::FileSummary(QWidget *parent) :
    QWidget(parent),
    ui_(new Ui::FileSummary),
    file_path_(QString("")),
    main_layout_(new QVBoxLayout(this)),
    parse_option_layout_(new QHBoxLayout()),
    main_content_layout_(new QGridLayout()),
    parse_option_(new preview_csv::ParseOption()),
    start_parse_button_(new QPushButton("解析")),
    file_info_(nullptr),
    table_lines_(QList<QStringList>()),
    row_count_(0),
    column_count_(0),
    column_names_(QList<QString>()),
    column_unique_count_(std::unordered_map<QString, int>()),
    column_unique_values_(std::unordered_map<QString, std::unordered_set<QString>>()),
    progress_bar_(new QProgressBar()),
    progress_timer_(new QTimer()),
    current_progress_value_(0),
    current_progress_status_(true),
    actual_end_line_(101) {
    ui_->setupUi(this);
    this->setLayout(this->main_layout_);
    this->main_layout_->setAlignment(Qt::AlignTop);
    this->parse_option_layout_->addWidget(this->parse_option_);
    this->parse_option_layout_->addWidget(this->start_parse_button_);
    this->main_layout_->addLayout(parse_option_layout_, 1);
    this->main_layout_->addWidget(this->progress_bar_, 1);
    this->main_layout_->addLayout(main_content_layout_, 9);
    for (int i = 0; i < 10; i++) {
        this->main_content_layout_->setColumnStretch(i, 1);
    }
    // 点击按钮则发送预览信息选项
    connect(this->start_parse_button_,
            &QPushButton::pressed,
            this->parse_option_,
            &preview_csv::ParseOption::sendParseInfo);
    // 发送预览信息之后则显示表格
    connect(this->parse_option_,
            &preview_csv::ParseOption::sendInfo,
            this,
            &preview_csv::FileSummary::getParseOption);
    // 轮询修改处理进度
    connect(this->progress_timer_, &QTimer::timeout, this, &preview_csv::FileSummary::setProgressValue);
}

preview_csv::FileSummary::~FileSummary() {
    delete ui_;
    // 析构的时候删掉数据
    this->clearData();
}

void preview_csv::FileSummary::insertSingleToRow(int row_index,
                                                 const QString &label_text,
                                                 const QString &content_text) {
    // 一行插入时按照标签与输入框1:9的比例插入
    auto *label_widget = new QLabel(label_text);
    this->main_content_layout_->addWidget(label_widget, row_index, 0, 1, 1);
    auto *label_content = new QLineEdit(content_text);
    this->main_content_layout_->addWidget(label_content, row_index, 1, 1, 9);
}

void preview_csv::FileSummary::insertDoubleToRow(int row_index,
                                                 int item_index,
                                                 const QString &label_text,
                                                 const QString &content_text) {
    // 插入两行时按照第一个标签、第一个框、空格、第二个标签、第二个框为1:3:1:1:3的比例插入
    int first_label_start = 0;  // 第一个item label开始位置
    int first_label_length = 1;  // 第一item label长度
    int first_content_start = first_label_start + first_label_length;  // 第一个item content开始位置
    int first_content_length = 3;  // 第一个item content长度

    int second_label_start = first_content_start + first_content_length + 1;  // 第二个item label开始位置
    int second_label_length = 1;  // 第二item label长度
    int second_content_start = second_label_start + second_label_length;  // 第二个item content开始位置
    int second_content_length = 3;  // 第二个item content长度

    if (item_index == 0) {
        auto *label_widget = new QLabel(label_text);
        this->main_content_layout_->addWidget(label_widget, row_index, first_label_start, 1, first_label_length);
        auto *label_content = new QLineEdit(content_text);
        this->main_content_layout_->addWidget(label_content, row_index, first_content_start, 1, first_content_length);
    } else if (item_index == 1) {
        auto *label_widget = new QLabel(label_text);
        this->main_content_layout_->addWidget(label_widget, row_index, second_label_start, 1, second_label_length);
        auto *label_content = new QLineEdit(content_text);
        this->main_content_layout_->addWidget(label_content, row_index, second_content_start, 1, second_content_length);
    } else {
        throw std::invalid_argument("只能为0或1");
    }
}

void preview_csv::FileSummary::insertSingleToRow(int row_index,
                                                 const QString &label_text,
                                                 const QString &first_content_text,
                                                 const QString &second_content_text) {
    // 按照标签、第一个框、第二个框1:1:8的比例插入
    auto *label_widget = new QLabel(label_text);
    this->main_content_layout_->addWidget(label_widget, row_index, 0, 1, 0);
    auto *first_label_content = new QLineEdit(first_content_text);
    this->main_content_layout_->addWidget(first_label_content, row_index, 1, 1, 1);
    auto *second_label_content = new QLineEdit(second_content_text);
    this->main_content_layout_->addWidget(second_label_content, row_index, 2, 1, 8);
}

void preview_csv::FileSummary::getFileInfo() {
    // 读取文件路径
    QFile file(this->file_path_);
    this->file_info_ = new FileInfo();
    // 获取文件名字
    QStringList separated_filename = file.fileName().split(QDir::separator());
    this->file_info_->file_name = separated_filename[separated_filename.size() - 1];
    // 获取文件大小，单位为m
    this->file_info_->file_size = QString::number((double) file.size() / 1048576.0);
    // 删除layout下的所有项目
    QLayoutItem *item;
    while ((item = this->main_content_layout_->takeAt(0)))
        if (item->widget()) {
            item->widget()->setParent(nullptr);
        }
    delete item;
    // 第一行插入文件名
    this->insertDoubleToRow(0, 0, "文件名", this->file_info_->file_name);
    // 第一行插入文件大小
    this->insertDoubleToRow(0, 1, "文件大小", this->file_info_->file_size);
    // 第二行插入行数
    this->insertDoubleToRow(1, 0, "行数", QString::number(this->row_count_));
    // 第二行插入列数
    this->insertDoubleToRow(1, 1, "列数", QString::number(this->column_count_));
    // 第三行开始每一行插入每列的名字、不重复值数量、不重复值
    int current_row = 2;
    for (auto &column_name: this->column_names_) {
        auto unique_column_value_string = QString();
        auto unique_values = this->column_unique_values_.find(column_name);
        for (const auto &word : unique_values->second) {
            unique_column_value_string = unique_column_value_string + word + ",";
        }
        QString count_string;
        if (this->column_unique_count_.find(column_name)->second >= 100) {
            count_string = QString("大于等于%1").arg(this->column_unique_count_.find(column_name)->second);
        } else {
            count_string = QString("%1").arg(this->column_unique_count_.find(column_name)->second);
        }
        this->insertSingleToRow(current_row,
                                column_name,
                                QString("%1").arg(count_string),
                                QString("%1").arg(unique_column_value_string));
        current_row++;
    }
}

void preview_csv::FileSummary::extractTableLines(int start_line,
                                                 int end_line,
                                                 const QString &line_sep) {
    // 打开文件
    QFile file(this->file_path_);
    if (!file.open(QFile::ReadOnly |
        QFile::Text)) {
        qDebug() << " Could not open the file for reading";
        return;
    }
    QTextStream in(&file);
    QStringList line_string_list;
    int row_index = 0;
    int row_count = 0, column_count = 0;
    // 读取每一行直到读到文件末尾或达到要求最大值
    while (!in.atEnd() && row_index < end_line) {
        QString f_file_line = in.readLine();//读取文件的一行

        if (row_index < start_line && row_index != 0) {
            row_index++;
            continue;
        }
        // 解析本行
        line_string_list = tools::CsvLineParser(f_file_line, line_sep).getParsedList();
        this->table_lines_.append(line_string_list);
        row_count++;
        // 如果某一行解析除了比现有列数更多的元素，则把现有列数更新为更大值
        if (column_count < line_string_list.size()) {
            column_count = line_string_list.size();
        }
        if (row_index == 0) {
            // 如果是第一行，则将本行作为列名保存
            if (!this->table_lines_.empty()) {
                for (int i = 0; i < this->table_lines_[0].size(); i++) {
                    // 更新列名，如果发现元素数量超过列名，则增加一个与列序号相关的名字
                    if (i < this->table_lines_[0].size()) {
                        this->column_names_.push_back(this->table_lines_[0][i]);
                    } else {
                        this->column_names_.push_back(QString("Column%1").arg(i));
                    }
                }
            }
        } else {
            // 如果不是第一行则更新每列的不重复值数量与不重复值
            for (int j = 0; j < line_string_list.size(); j++) {
                if (j >= this->column_names_.size()) {
                    this->column_names_.push_back(QString("Column%1").arg(j));
                }
                auto existed_record = this->column_unique_values_.find(this->column_names_[j]);
                if (existed_record != this->column_unique_values_.end()) {
                    auto column_unique_count = this->column_unique_count_.find(this->column_names_[j]);
                    if (column_unique_count->second >= 100) {
                        continue;
                    }
                    existed_record->second.insert(line_string_list[j]);
                    column_unique_count->second = existed_record->second.size();
                } else {
                    auto value_set = std::unordered_set<QString>();
                    value_set.insert(line_string_list[j]);
                    this->column_unique_values_.insert(std::make_pair(this->column_names_[j], value_set));
                    auto less_enough_pair = std::make_pair(this->column_names_[j], 1);
                    this->column_unique_count_.insert(less_enough_pair);
                }
            }
        }
        row_index++;
        this->current_progress_value_ = row_index;
    }
    this->row_count_ = this->table_lines_.size();
    this->column_count_ = column_count;
    this->actual_end_line_ = start_line + this->row_count_;
    file.close();//关闭文件

}

void preview_csv::FileSummary::clearData() {
    for (auto &line: this->table_lines_) {
        line.clear();
    }
    this->table_lines_.clear();
    for (auto &line: this->column_unique_values_) {
        line.second.clear();
    }
    this->column_unique_values_.clear();
    this->column_names_.clear();
    this->column_unique_count_.clear();
}

void preview_csv::FileSummary::getParseOption(int start_line, int end_line, const QString &line_sep) {
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
        this->clearData();
        // 创建轮询timer
        this->progress_timer_->start(100);
        // 创建后台任务子进程。
        this->back_ground_ = std::thread(&preview_csv::FileSummary::extractTableLines,
                                         this,
                                         start_line,
                                         end_line,
                                         line_sep);
    }
}
void preview_csv::FileSummary::setProgressValue() {
    // 此为轮询任务，每次轮询会将当前的progress设置为读取到的值
    this->progress_bar_->setValue(this->current_progress_value_);
    this->progress_bar_->update();
    if (this->current_progress_value_ == this->actual_end_line_) {
        // 如果轮询时发现当前进度跟计算的总进度一致，那么停止任务并开始渲染。
        this->progress_bar_->setMaximum(this->actual_end_line_);
        this->back_ground_.join();
        this->getFileInfo();
        this->progress_timer_->stop();
        // 标记状态为可查询
        this->current_progress_status_ = true;
    }
}
void preview_csv::FileSummary::receiveFilePath(QString file_path) {
    this->file_path_ = std::move(file_path);
    this->start_parse_button_->animateClick();
}