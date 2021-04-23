//
// Created by 徐秋实 on 2021/3/23.
//

// You may need to build the project (run Qt uic code generator) to get "ui_clipboard_picture_viewer.h" resolved
#include <QApplication>
#include <QMimeData>
#include <QClipboard>
#include <QPixmap>
#include <QByteArray>
#include <QBuffer>
#include <QDebug>
#include "clipboard_picture_viewer.h"

picture_to_base64::ClipboardPictureViewer::ClipboardPictureViewer(QWidget *parent) :
    QLabel(parent), image_data_(new QImage()) {
    this->setText("点击此处后粘贴图片");
    this->setAlignment(Qt::AlignCenter);
    this->setFocusPolicy(Qt::ClickFocus);
}

picture_to_base64::ClipboardPictureViewer::~ClipboardPictureViewer() {
}

void picture_to_base64::ClipboardPictureViewer::keyPressEvent(QKeyEvent *ev) {
    if (ev->type() == QKeyEvent::KeyPress) {
        if (ev->matches(QKeySequence::Paste)) {
            qDebug() << ev;
            const QClipboard *clipboard = QApplication::clipboard();
            const QMimeData *mime_data = clipboard->mimeData();
            if (mime_data->hasImage()) {
                *this->image_data_ = mime_data->imageData().value<QImage>();
                this->setPixmap(QPixmap::fromImage(*this->image_data_));
                QByteArray byte_array;
                QBuffer buffer(&byte_array);
                this->image_data_->save(&buffer, "PNG"); // writes the image in PNG format inside the buffer
                QString base_64 = QString::fromLatin1(byte_array.toBase64().data());
                emit this->sendBase64(QString("%1%2").arg("data:image/png;base64,", base_64));
            }
        }
    }
}
