//
// Created by 徐秋实 on 2021/2/23.
//

// You may need to build the project (run Qt uic code generator) to get "ui_FileEncodingTransformDragResult.h" resolved

#include "result_view.h"
#include "ui_result_view.h"

file_encoding_transform::ResultView::ResultView(QWidget *parent) :
    QWidget(parent), ui_(new Ui::FileEncodingTransformResult) {
    ui_->setupUi(this);
    ui_->listView->setModel(this->transformed_file_model_);
    ui_->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

file_encoding_transform::ResultView::~ResultView() {
    delete ui_;
}

void file_encoding_transform::ResultView::ReceiveTransformedFile(const QString &transformed_file_path) {
    int next_position = this->transformed_file_model_->rowCount();
    this->transformed_file_model_->insertRows(next_position, 1);
    QModelIndex edit_index = this->transformed_file_model_->index(next_position);
    this->transformed_file_model_->setData(edit_index, transformed_file_path);
}