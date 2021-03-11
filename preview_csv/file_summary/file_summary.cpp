//
// Created by 徐秋实 on 2021/3/9.
//

// You may need to build the project (run Qt uic code generator) to get "ui_file_summary.h" resolved

#include <QLabel>
#include <QTextEdit>
#include <QLineEdit>
#include <exception>
#include "file_summary.h"
#include "ui_file_summary.h"

preview_csv::FileSummary::FileSummary(QWidget *parent) :
    QWidget(parent), ui_(new Ui::FileSummary), main_layout_(new QGridLayout(this)) {
    ui_->setupUi(this);
    this->setLayout(this->main_layout_);
    for (int i = 0; i < 10; i++) {
        this->main_layout_->setColumnStretch(i, 1);
    }
    this->insertDoubleToRow(0, 0, "文件名", "测试文件名字");
    this->insertDoubleToRow(0, 1, "文件大小", "测试文件大小");
    this->insertDoubleToRow(1, 0, "行数", "测试行数");
    this->insertDoubleToRow(1, 1, "列数", "测试列数");
    this->insertDoubleToRow(2, 0, "行数", "测试行数");
    this->insertDoubleToRow(2, 1, "列数", "测试列数");
    this->insertDoubleToRow(3, 0, "行数", "测试行数");
    this->insertDoubleToRow(3, 1, "列数", "测试列数");
    this->insertDoubleToRow(4, 0, "行数", "测试行数");
    this->insertDoubleToRow(4, 1, "列数", "测试列数");
    this->insertSingleToRow(5, "测试单行", "测试单行");
}

preview_csv::FileSummary::~FileSummary() {
    delete ui_;
}

void preview_csv::FileSummary::insertSingleToRow(int row_index, const QString& label_text, const QString& content_text) {
    auto *label_widget = new QLabel(label_text);
    this->main_layout_->addWidget(label_widget, row_index, 0, 1, 0);
    auto *label_content = new QLineEdit(content_text);
    this->main_layout_->addWidget(label_content, row_index, 2, 1, 9);
}

void preview_csv::FileSummary::insertDoubleToRow(int row_index,
                                                 int item_index,
                                                 const QString& label_text,
                                                 const QString& content_text) {
    int first_label_start = 0;  // 第一个item label开始位置
    int first_label_length = 1;  // 第一item label长度
    int first_content_start = first_label_start + first_label_length;  // 第一个item content开始位置
    int first_content_length = 3;  // 第一个item content长度

    int second_label_start = first_content_start + first_content_length + 1;  // 第二个item label开始位置
    int second_label_length = 1;  // 第二item label长度
    int second_content_start = second_label_start + second_label_length;  // 第二个item content开始位置
    int second_content_length = 3;  // 第二个item content长度

    if(item_index == 0) {
        auto *label_widget = new QLabel(label_text);
        this->main_layout_->addWidget(label_widget, row_index, first_label_start, 1, first_label_length);
        auto *label_content = new QLineEdit(content_text);
        this->main_layout_->addWidget(label_content, row_index, first_content_start, 1, first_content_length);
    } else if (item_index == 1) {
        auto *label_widget = new QLabel(label_text);
        this->main_layout_->addWidget(label_widget, row_index, second_label_start, 1, second_label_length);
        auto *label_content = new QLineEdit(content_text);
        this->main_layout_->addWidget(label_content, row_index, second_content_start, 1, second_content_length);
    } else {
        throw std::invalid_argument("只能为0或1");
    }
}
