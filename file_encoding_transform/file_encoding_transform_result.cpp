//
// Created by 徐秋实 on 2021/2/23.
//

// You may need to build the project (run Qt uic code generator) to get "ui_FileEncodingTransformDragResult.h" resolved

#include "file_encoding_transform_result.h"
#include "ui_file_encoding_transform_result.h"

FileEncodingTransformResult::FileEncodingTransformResult(QWidget *parent) :
        QWidget(parent), ui(new Ui::FileEncodingTransformResult) {
    ui->setupUi(this);
    ui->listView->setModel(this->transformedFileModel);
    ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

FileEncodingTransformResult::~FileEncodingTransformResult() {
    delete ui;
}

void FileEncodingTransformResult::receiveTransformedFile(const QString &transformedFilePath) {
    int nextPosition = this->transformedFileModel->rowCount();
    this->transformedFileModel->insertRows(nextPosition, 1);
    QModelIndex editIndex = this->transformedFileModel->index(nextPosition);
    this->transformedFileModel->setData(editIndex, transformedFilePath);
}