//
// Created by 徐秋实 on 2021/3/4.
//

// You may need to build the project (run Qt uic code generator) to get "ui_main_view.h" resolved
#include <QVBoxLayout>
#include <QFile>
#include <QDebug>
#include <QPushButton>
#include "main_view.h"
#include "preview_csv/ui_main_view.h"
#include "file_path_getter.h"
#include "parse_option.h"
#include "custom_csv_model.h"

preview_csv::MainView::MainView(QWidget *parent) :
    QWidget(parent),
    ui_(new Ui::MainView),
    table_view_(new QTableView()),
    table_data_(new preview_csv::CustomCsvModel()) {
    ui_->setupUi(this);
    this->table_view_->setModel(this->table_data_);
    // 创建垂直布局
    auto *layout = new QVBoxLayout();
    // 第一行保存文件路径
    auto *file_path_line = new preview_csv::FilePathGetter("拖拽文件至此");
    file_path_line->setDragEnabled(true);
    layout->addWidget(file_path_line, 1);
    // 第二行控制解析选项
    auto *parse_option_layout = new QHBoxLayout();
    auto *parse_option = new preview_csv::ParseOption();
    parse_option_layout->addWidget(parse_option);
    auto *start_parse_button = new QPushButton("预览");
    parse_option_layout->addWidget(start_parse_button);
    layout->addLayout(parse_option_layout);
    connect(start_parse_button, &QPushButton::pressed, parse_option, &preview_csv::ParseOption::sendParseInfo);
    // 最后放置预览界面
    layout->addWidget(this->table_view_, 9);
    this->setLayout(layout);
    connect(file_path_line, &preview_csv::FilePathGetter::emitFilePath, this, &preview_csv::MainView::getFileInfo);
    connect(parse_option, &preview_csv::ParseOption::sendInfo, this, &preview_csv::MainView::getParseOption);
}

preview_csv::MainView::~MainView() {
    delete ui_;
}

void preview_csv::MainView::setTableLines(const QString &file_path,
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
        line_string_list = preview_csv::MainView::parseCsv(f_file_line, line_sep);
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

void preview_csv::MainView::getFileInfo(const QString &file_path) {
    this->file_path_ = file_path;
    this->setTableLines(file_path, 0, 100, ",");
}

void preview_csv::MainView::getParseOption(int start_line, int end_line, const QString &line_sep) {
    this->setTableLines(this->file_path_, start_line, end_line, line_sep);
}

QStringList preview_csv::MainView::parseCsv(const QString &string, const QString &line_sep) {
    enum State { NORMAL, QUOTE } state = NORMAL;
    QStringList fields;
    QString value;

    for (int i = 0; i < string.size(); i++) {
        const QChar kCurrent = string.at(i);

        // Normal state
        if (state == NORMAL) {
            // Comma
            if (kCurrent == line_sep) {
                // Save field
                fields.append(value.trimmed());
                value.clear();
            }

                // Double-quote
            else if (kCurrent == '"') {
                state = QUOTE;
                value += kCurrent;
            }

                // Other character
            else
                value += kCurrent;
        }

            // In-quote state state == QUOTE
        else {
            // Another double-quote
            if (kCurrent == '"') {
                if (i < string.size()) {
                    // A double double-quote?
                    if (i + 1 < string.size() && string.at(i + 1) == '"') {
                        value += '"';

                        // Skip a second quote character in a row
                        i++;
                    } else {
                        state = NORMAL;
                        value += '"';
                    }
                }
            }

                // Other character
            else
                value += kCurrent;
        }
    }

    if (!value.isEmpty())
        fields.append(value.trimmed());

    // Quotes are left in until here; so when fields are trimmed, only whitespace outside of
    // quotes is removed.  The quotes are removed here.
    for (int i = 0; i < fields.size(); ++i)
        if (fields[i].length() >= 1 && fields[i].left(1) == '"') {
            fields[i] = fields[i].mid(1);
            if (fields[i].length() >= 1 && fields[i].right(1) == '"')
                fields[i] = fields[i].left(fields[i].length() - 1);
        }

    return fields;
}