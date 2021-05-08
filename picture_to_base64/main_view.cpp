//
// Created by 徐秋实 on 2021/3/23.
//

// You may need to build the project (run Qt uic code generator) to get "ui_main_view.h" resolved

#include <QMessageBox>
#include "main_view.h"
#include "picture_to_base64/ui_main_view.h"

picture_to_base64::MainView::MainView(QWidget *parent) :
    QWidget(parent),
    ui_(new picture_to_base64::Ui::MainView),
    save_button_(new QPushButton("保存")),
    save_dialog_(new QFileDialog()),
    main_layout_(new QVBoxLayout()),
    clipboard_picture_viewer_(new ClipboardPictureViewer()),
    base_64_result_(new QTextEdit()) {
    ui_->setupUi(this);
    this->setLayout(main_layout_);
    main_layout_->addWidget(this->save_button_);
    main_layout_->addWidget(this->clipboard_picture_viewer_, 1);
    main_layout_->addWidget(this->base_64_result_, 1);
    connect(this->clipboard_picture_viewer_,
            &picture_to_base64::ClipboardPictureViewer::sendBase64,
            this,
            &picture_to_base64::MainView::receiveBaseString);
    connect(this->save_button_,
            &QPushButton::pressed,
            this->clipboard_picture_viewer_,
            &ClipboardPictureViewer::startSendImageForSave);
    connect(
        this->clipboard_picture_viewer_,
        &ClipboardPictureViewer::sendImageForSave,
        this,
        &MainView::saveImage
    );
}

picture_to_base64::MainView::~MainView() {
    delete ui_;
}

void picture_to_base64::MainView::receiveBaseString(const QString &base_64_string) {
    this->base_64_result_->setText(base_64_string);
}
void picture_to_base64::MainView::saveImage(QImage *image) {
    QString file_name = QFileDialog::getSaveFileName(
        this,
        tr("Save Address Book"),
        "/",
        tr("All Files (*)"));
    if (file_name.isEmpty())
        return;
    else {
        QFile file(file_name);
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::information(this, tr("Unable to open file"),
                                     file.errorString());
        } else {
            image->save(&file, "png");
        }
        file.close();
    }
}
