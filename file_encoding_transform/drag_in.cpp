//
// Created by 徐秋实 on 2021/2/23.
//

// You may need to build the project (run Qt uic code generator) to get "ui_file_encoding_transform_drag_in.h" resolved
#include <QDebug>
#include <QDropEvent>
#include <QMimeData>
#include <QProxyStyle>
#include <QGraphicsOpacityEffect>
#include <QAbstractItemView>
#include <QMessageBox>
#include "drag_in.h"
#include "ui_drag_in.h"
#include "drag_in_style.h"

file_encoding_transform::DragIn::DragIn(QWidget *parent) :
    QWidget(parent), ui_(new Ui::DragIn) {
    ui_->setupUi(this);
    this->setAcceptDrops(true);
    ui_->listView->setModel(this->file_list_model_);
    ui_->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

file_encoding_transform::DragIn::~DragIn() {
    delete ui_;
}

void file_encoding_transform::DragIn::dropEvent(QDropEvent *event) {
    qDebug() << event;
    ui_->listView->setStyle(new QProxyStyle);
    int next_position;
    QModelIndex edit_index;
    for (const QUrl &url: event->mimeData()->urls()) {
        QString file_name = url.toLocalFile();
        qDebug() << "Dropped file:" << file_name;
        next_position = this->file_list_model_->rowCount();
        if (!this->file_list_model_->insertRows(next_position, 1)) {
            QMessageBox::StandardButton confirm = QMessageBox::warning(this, "Warning", "选择文件失败");
            qDebug() << confirm;
        }
        edit_index = this->file_list_model_->index(next_position);
        if (!this->file_list_model_->setData(edit_index, file_name)) {
            QMessageBox::StandardButton confirm = QMessageBox::warning(this, "Warning", "修改失败");
            qDebug() << confirm;
        }
    }
    ui_->listView->viewport()->setAutoFillBackground(true);
}

void file_encoding_transform::DragIn::dragEnterEvent(QDragEnterEvent *event) {
    qDebug() << event->mimeData()->formats();
    event->acceptProposedAction();
    ui_->listView->setStyle(new CustomDragInStyle);
    ui_->listView->viewport()->setAutoFillBackground(false);
}

void file_encoding_transform::DragIn::dragLeaveEvent(QDragLeaveEvent *event) {
    ui_->listView->setStyle(new QProxyStyle);
    ui_->listView->viewport()->setAutoFillBackground(true);
}

void file_encoding_transform::DragIn::BeginSend() {
    emit this->SendFileList(this->file_list_model_);
}