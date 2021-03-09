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
    preview_content_layout_(new QVBoxLayout()),
    parse_option_layout_(new QHBoxLayout()),
    parse_option_(new preview_csv::ParseOption()) {
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
}

preview_csv::PreviewContent::~PreviewContent() {
    delete ui_;
    delete preview_content_layout_;
//    delete parse_option_layout_;
//    delete parse_option_;
//    delete start_parse_button_;
//    delete table_view_;
//    delete table_data_;
}

void preview_csv::PreviewContent::setTableLines(const QString &file_path,
                                                int start_line,
                                                int end_line,
                                                const QString &line_sep) {
    QFile file(file_path);
    if (!file.open(QFile::ReadOnly |
        QFile::Text)) {
        qDebug() << " Could not open the file for reading";
        return;
    }
    QTextStream in(&file);
    this->table_data_->clear();//清空
    QStringList line_string_list;
    int row_index = 0;
    int row_count = 0, column_count = 0;
    QList<QStringList> csv_data;
    while (!in.atEnd() && row_index < end_line) {
        QString f_file_line = in.readLine();//读取文件的一行
        if (row_index < start_line && row_index != 0) {
            row_index++;
            continue;
        }
        line_string_list = tools::CsvLineParser(f_file_line, line_sep).getParsedList();
        csv_data.append(line_string_list);
        row_count++;
        if (column_count < line_string_list.size()) {
            column_count = line_string_list.size();
        }
        row_index++;
    }
    file.close();//关闭文件
    this->table_data_->setCsvData(row_count, column_count, csv_data);
}

void preview_csv::PreviewContent::getParseOption(int start_line, int end_line, const QString &line_sep) {
    if (!this->file_path_.isEmpty()) {
        this->setTableLines(this->file_path_, start_line, end_line, line_sep);
    }
}

void preview_csv::PreviewContent::receiveFilePath(QString file_path) {
    this->file_path_ = std::move(file_path);
    this->start_parse_button_->animateClick();
}
