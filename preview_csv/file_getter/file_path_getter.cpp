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
    this->setStyleSheet("QLineEdit{ "
                    "background-color:rgb(202, 255, 227);"
                    "border: 2px solid gray;}"
    );
    event->acceptProposedAction();
}

void preview_csv::FilePathGetter::dragLeaveEvent(QDragLeaveEvent *event) {
    this->setStyleSheet("");
}

void preview_csv::FilePathGetter::dropEvent(QDropEvent *event) {
    this->file_path_ = event->mimeData()->urls()[0].toLocalFile();
    this->setText(this->file_path_);
    this->setStyleSheet("");
    qDebug() << this->file_path_;
    emit this->emitFilePath(this->file_path_);
}
