//
// Created by 徐秋实 on 2021/2/23.
//

// You may need to build the project (run Qt uic code generator) to get "ui_file_encoding_transform_drag_in.h" resolved
#include <QDebug>
#include <QDropEvent>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QProxyStyle>
#include <QGraphicsOpacityEffect>
#include <QAbstractItemView>
#include "file_encoding_transform_drag_in.h"
#include "ui_file_encoding_transform_drag_in.h"
#include "file_encoding_transform_drag_in_style.h"


FileEncodingTransformDragIn::FileEncodingTransformDragIn(QWidget *parent) :
        QWidget(parent), ui(new Ui::FileEncodingTransformDragIn) {
    ui->setupUi(this);
    this->setAcceptDrops(true);
    ui->listView->setModel(this->fileListModel);
    ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

FileEncodingTransformDragIn::~FileEncodingTransformDragIn() {
    delete ui;
}

void FileEncodingTransformDragIn::dropEvent(QDropEvent *event) {
    qDebug() << event;
    ui->listView->setStyle(new QProxyStyle);
    int nextPosition;
    QModelIndex editIndex;
    for (const QUrl &url: event->mimeData()->urls()) {
        QString fileName = url.toLocalFile();
        qDebug() << "Dropped file:" << fileName;
        nextPosition = this->fileListModel->rowCount();
        this->fileListModel->insertRows(nextPosition, 1);
        editIndex = this->fileListModel->index(nextPosition);
        this->fileListModel->setData(editIndex, fileName);
    }
    ui->listView->viewport()->setAutoFillBackground(true);
}

void FileEncodingTransformDragIn::dragEnterEvent(QDragEnterEvent *event) {
    qDebug() << event->mimeData()->formats();
    event->acceptProposedAction();
    ui->listView->setStyle(new CustomDragInStyle);
    ui->listView->viewport()->setAutoFillBackground(false);
}

void FileEncodingTransformDragIn::dragLeaveEvent(QDragLeaveEvent *event) {
    ui->listView->setStyle(new QProxyStyle);
    ui->listView->viewport()->setAutoFillBackground(true);
}

void FileEncodingTransformDragIn::beginSend() {
    emit this->sendFileList(this->fileListModel);
}