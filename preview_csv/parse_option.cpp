//
// Created by 徐秋实 on 2021/3/5.
//

// You may need to build the project (run Qt uic code generator) to get "ui_ParseOption.h" resolved

#include <QHBoxLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QLabel>
#include <QRegExpValidator>
#include <QRegExp>
#include "parse_option.h"
#include "ui_parse_option.h"

preview_csv::ParseOption::ParseOption(QWidget *parent) :
    QWidget(parent), ui_(new Ui::ParseOption) {
    ui_->setupUi(this);
    auto *parse_options_layout = new QHBoxLayout();
    this->start_line_ = new QLineEdit("0");
    auto *reg = new QRegExpValidator(QRegExp("^\\d+$"));
    this->start_line_->setValidator(reg);
    this->end_line_ = new QLineEdit("101");
    this->end_line_->setValidator(reg);
    this->line_sep_ = new QComboBox();
    this->line_sep_->addItem(",");
    this->line_sep_->addItem("\\t");
    parse_options_layout->addWidget(new QLabel("start line"));
    parse_options_layout->addWidget(start_line_);
    parse_options_layout->addWidget(new QLabel("end line"));
    parse_options_layout->addWidget(end_line_);
    parse_options_layout->addWidget(new QLabel("line sep"));
    parse_options_layout->addWidget(line_sep_);
    this->setLayout(parse_options_layout);
}

preview_csv::ParseOption::~ParseOption() {
    delete ui_;
}

void preview_csv::ParseOption::sendParseInfo() {
    int start_line = this->start_line_->text().toInt();
    int end_line = this->end_line_->text().toInt();
    QString line_sep = this->line_sep_->currentText().replace("\\t", "\t");
    emit this->sendInfo(start_line, end_line, line_sep);
}
