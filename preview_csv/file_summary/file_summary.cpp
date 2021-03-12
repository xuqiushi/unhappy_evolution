//
// Created by 徐秋实 on 2021/3/9.
//

// You may need to build the project (run Qt uic code generator) to get "ui_file_summary.h" resolved

#include <filesystem>
#include <QFile>
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
    column_unique_values_(std::unordered_map<QString, std::unordered_set<QString>>()) {
    ui_->setupUi(this);
    this->setLayout(this->main_layout_);
    this->main_layout_->setAlignment(Qt::AlignTop);
    this->parse_option_layout_->addWidget(this->parse_option_);
    this->parse_option_layout_->addWidget(this->start_parse_button_);
    this->main_layout_->addLayout(parse_option_layout_, 1);
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
}

preview_csv::FileSummary::~FileSummary() {
    delete ui_;
}

void preview_csv::FileSummary::insertSingleToRow(int row_index,
                                                 const QString &label_text,
                                                 const QString &content_text) {
    auto *label_widget = new QLabel(label_text);
    this->main_content_layout_->addWidget(label_widget, row_index, 0, 1, 0);
    auto *label_content = new QLineEdit(content_text);
    this->main_content_layout_->addWidget(label_content, row_index, 1, 1, 9);
}

void preview_csv::FileSummary::insertDoubleToRow(int row_index,
                                                 int item_index,
                                                 const QString &label_text,
                                                 const QString &content_text) {
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

void preview_csv::FileSummary::getFileInfo(int start_line, int end_line, const QString &line_sep) {
    std::filesystem::path file_path(this->file_path_.toStdString().c_str());
    this->file_info_ = new FileInfo();
    this->file_info_->file_name = QString::fromStdString(file_path.filename().string());
    this->file_info_->file_size = QString::number((double) std::filesystem::file_size(file_path) / 1048576.0);
    QLayoutItem *item;
    while ((item = this->main_content_layout_->takeAt(0)))
        if (item->widget()) {
            item->widget()->setParent(nullptr);
        }
    delete item;
    this->insertDoubleToRow(0, 0, "文件名", this->file_info_->file_name);
    this->insertDoubleToRow(0, 1, "文件大小", this->file_info_->file_size);
    this->extractTableLines(start_line, end_line, line_sep);
    this->insertDoubleToRow(1, 0, "行数", QString::number(this->row_count_));
    this->insertDoubleToRow(1, 1, "列数", QString::number(this->column_count_));
    int current_row = 2;
    for (auto &column_name: this->column_names_) {
        auto unique_column_value_string = QString();
        auto unique_values = this->column_unique_values_.find(column_name);
        for (const auto &word : unique_values->second) {
            unique_column_value_string = unique_column_value_string + word + ",";
        }
        this->insertSingleToRow(current_row,
                                column_name,
                                QString("%1:%2").arg(QString::number(this->column_unique_values_.find(column_name)->second.size()),
                                                     unique_column_value_string));
        current_row++;
    }
}

void preview_csv::FileSummary::extractTableLines(int start_line,
                                                 int end_line,
                                                 const QString &line_sep) {
    QFile file(this->file_path_);
    if (!file.open(QFile::ReadOnly |
        QFile::Text)) {
        qDebug() << " Could not open the file for reading";
        return;
    }
    QTextStream in(&file);
    for (auto &line: this->table_lines_) {
        line.clear();
    }
    this->table_lines_.clear();
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
        this->table_lines_.append(line_string_list);
        row_count++;
        if (column_count < line_string_list.size()) {
            column_count = line_string_list.size();
        }
        if (row_index == 0) {
            if (!this->table_lines_.empty()) {
                for (int i = 0; i < this->table_lines_[0].size(); i++) {
                    if (i < this->table_lines_[0].size()) {
                        this->column_names_.push_back(this->table_lines_[0][i]);
                    } else {
                        this->column_names_.push_back(QString("Column%1").arg(i));
                    }
                }
            }
        } else {
            for (int j = 0; j < line_string_list.size(); j++) {
                if (j >= this->column_names_.size()) {
                    this->column_names_.push_back(QString("Column%1").arg(j));
                }
                auto existed_record = this->column_unique_values_.find(this->column_names_[j]);
                if (existed_record != this->column_unique_values_.end()) {
                    existed_record->second.insert(line_string_list[j]);
                } else {
                    auto value_set = std::unordered_set<QString>();
                    value_set.insert(line_string_list[j]);
                    this->column_unique_values_.insert(std::make_pair(this->column_names_[j], value_set));
                }
            }
        }
        row_index++;
    }
    this->row_count_ = this->table_lines_.size();
    this->column_count_ = column_count;
    file.close();//关闭文件

}

void preview_csv::FileSummary::getParseOption(int start_line, int end_line, const QString &line_sep) {
    if (!this->file_path_.isEmpty()) {
        this->getFileInfo(start_line, end_line, line_sep);
    }
}

void preview_csv::FileSummary::receiveFilePath(QString file_path) {
    this->file_path_ = std::move(file_path);
    this->start_parse_button_->animateClick();
}