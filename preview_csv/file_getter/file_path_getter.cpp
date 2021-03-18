//
// Created by 徐秋实 on 2021/3/4.
//

// You may need to build the project (run Qt uic code generator) to get "ui_file_path_getter.h" resolved
#include <QDebug>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QFile>
#include "file_path_getter.h"

preview_csv::FilePathGetter::FilePathGetter(const QString &text) : QLineEdit(text) {
}

preview_csv::FilePathGetter::~FilePathGetter() = default;

void preview_csv::FilePathGetter::dragEnterEvent(QDragEnterEvent *event) {
    // 如果进入范围，则改变背景颜色与边框，进行标示。
    this->setStyleSheet("QLineEdit{ "
                    "background-color:rgb(202, 255, 227);"
                    "border: 2px solid gray;}"
    );
    // 不知道有什么作用，参照官网复制来的。
    event->acceptProposedAction();
}

void preview_csv::FilePathGetter::dragLeaveEvent(QDragLeaveEvent *event) {
    // 如果离开了范围则重置背景与边框
    this->setStyleSheet("");
}

void preview_csv::FilePathGetter::dropEvent(QDropEvent *event) {
    // 如果放置下去则设置文件路径
    this->file_path_ = event->mimeData()->urls()[0].toLocalFile();
    // 直接把文件路径显示出来
    this->setText(this->file_path_);
    // 重置背景与边框
    this->setStyleSheet("");
    // 发送一个信号传输这个file_path_
    emit this->emitFilePath(this->file_path_);
}
