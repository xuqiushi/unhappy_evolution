//
// Created by 徐秋实 on 2021/3/4.
//

// You may need to build the project (run Qt uic code generator) to get "ui_main_view.h" resolved
#include <QLineEdit>
#include <QVBoxLayout>
#include <QFile>
#include <QDebug>
#include "main_view.h"
#include "preview_csv/ui_main_view.h"
#include "file_path_getter.h"

preview_csv::MainView::MainView(QWidget *parent) :
    QWidget(parent), ui_(new Ui::MainView), table_view_(new QTableView()), table_data_(new QStandardItemModel()) {
    ui_->setupUi(this);
    this->table_view_->setModel(this->table_data_);
    // 创建垂直布局
    auto *layout = new QVBoxLayout();
    // 第一行保存文件路径
    auto *file_path_line = new preview_csv::FilePathGetter("拖拽文件至此");
    file_path_line->setDragEnabled(true);

    layout->addWidget(file_path_line, 1);
    layout->addWidget(this->table_view_, 9);
    this->setLayout(layout);
    connect(file_path_line, &preview_csv::FilePathGetter::emitFilePath, this, &preview_csv::MainView::getFileInfo);
}

preview_csv::MainView::~MainView() {
    delete ui_;
}

void preview_csv::MainView::getFileInfo(const QString &file_path) {
    QFile file(file_path);
    if (!file.open(QFile::ReadOnly |
        QFile::Text)) {
        qDebug() << " Could not open the file for reading";
        return;
    }
    QTextStream in(&file);
    QString first_line = in.readLine();
    qDebug() << first_line;
    file.close();
    QStringList first_line_list = first_line.split(",");
    qDebug() << first_line_list;
    this->table_data_->setColumnCount(first_line_list.size());
//    this->table_data_->setHorizontalHeaderLabels(first_line_list);

    QFile content_file(file_path);  //以文件方式读出
    if (content_file.open(QIODevice::ReadOnly | QIODevice::Text)) //以只读文本方式打开文件
    {
        QTextStream content_stream(&content_file); //用文本流读取文件
        this->table_data_->clear();//清空
        QStringList line_string_list;
        int row_count = 0;
        while (!content_stream.atEnd() && row_count < 100)
        {
            QString f_file_line=content_stream.readLine();//读取文件的一行
            QStandardItem *tmp_item;
            line_string_list = f_file_line.split(",");
            this->table_data_->insertRow(row_count);
            for (int i = 0; i < first_line_list.size(); i++){
                if (i < line_string_list.size()) {
                    tmp_item = new QStandardItem(line_string_list[i]);
                    this->table_data_->setItem(row_count, i, tmp_item);
                }
            }
            row_count ++;
        }
        content_file.close();//关闭文件
    }

}