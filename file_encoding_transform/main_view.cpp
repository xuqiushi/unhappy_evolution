//
// Created by 徐秋实 on 2021/2/23.
//

// You may need to build the project (run Qt uic code generator) to get "ui_file_encoding_transform_main.h" resolved
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QTextCodec>
#include <QFileInfo>
#include <QDir>
#include <QRegularExpression>
#include "main_view.h"
#include "ui_main_view.h"
#include "drag_in.h"
#include "result_view.h"

file_encoding_transform::MainView::MainView(QWidget *parent) :
    QWidget(parent), ui_(new Ui::FileEncodingTransformMain) {
    ui_->setupUi(this);
    auto file_encoding_transform_drag_in = new file_encoding_transform::DragIn();
    auto file_encoding_transform_result = new file_encoding_transform::ResultView();

    auto *main_layout = new QHBoxLayout();
    auto *v_layout = new QVBoxLayout();
    auto *right_arrow = new QPushButton("转换为");
    v_layout->addWidget(right_arrow);
    main_layout->addWidget(file_encoding_transform_drag_in);
    main_layout->addLayout(v_layout);
    main_layout->addWidget(file_encoding_transform_result);

    this->setLayout(main_layout);
    connect(right_arrow, &QPushButton::pressed, file_encoding_transform_drag_in,
            &file_encoding_transform::DragIn::BeginSend);
    connect(file_encoding_transform_drag_in, &file_encoding_transform::DragIn::SendFileList, this,
            &file_encoding_transform::MainView::TransformFiles);
    connect(this, &file_encoding_transform::MainView::SendTransformedFile, file_encoding_transform_result,
            &file_encoding_transform::ResultView::ReceiveTransformedFile);
}

file_encoding_transform::MainView::~MainView() {
    delete ui_;
}

void file_encoding_transform::MainView::TransformFiles(QStringListModel *file_list_model) {
    qDebug() << file_list_model->stringList();
    for (int i = 0; i < file_list_model->rowCount(); i++) {
        qDebug() << file_list_model->data(file_list_model->index(i)).toString();
        QFile file(file_list_model->data(file_list_model->index(i)).toString());
        if (!file.open(QFile::ReadOnly |
            QFile::Text)) {
            qDebug() << " Could not open the file for reading";
            return;
        }

        QTextStream in(&file);
        QString text_string = in.readAll();
        qDebug() << text_string;
        file.close();
        QTextCodec *codec = QTextCodec::codecForName("GB18030");
        QByteArray output_bytes = codec->fromUnicode(text_string);
        QFileInfo old_file_info = QFileInfo(file_list_model->data(file_list_model->index(i)).toString());
        QString old_filename = old_file_info.fileName();
        QDir old_file_dir = old_file_info.absoluteDir();
        QRegularExpression regex("^(.*)(\\..+)");
        qDebug() << old_filename;
        qDebug() << old_file_dir;
        QString new_filename = old_filename.replace(regex, "\\1_gbk\\2");
        QString new_file_path = old_file_dir.filePath(new_filename);
        QFile output_file(new_file_path);
        if (!output_file.open(QFile::WriteOnly)) {
            qDebug() << " Could not open the file for writing";
            return;
        }
        output_file.write(output_bytes);
        output_file.close();
        emit this->SendTransformedFile(new_file_path);
    }
}
