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
#include "file_encoding_transform_main.h"
#include "ui_file_encoding_transform_main.h"
#include "file_encoding_transform_drag_in.h"
#include "file_encoding_transform_result.h"


FileEncodingTransformMain::FileEncodingTransformMain(QWidget *parent) :
        QWidget(parent), ui(new Ui::FileEncodingTransformMain) {
    ui->setupUi(this);
    auto file_encoding_transform_drag_in = new FileEncodingTransformDragIn();
    auto file_encoding_transform_result = new FileEncodingTransformResult();

    auto *main_layout = new QHBoxLayout();
    auto *v_layout = new QVBoxLayout();
    auto *right_arrow = new QPushButton("转换为");
    v_layout->addWidget(right_arrow);
    main_layout->addWidget(file_encoding_transform_drag_in);
    main_layout->addLayout(v_layout);
    main_layout->addWidget(file_encoding_transform_result);

    this->setLayout(main_layout);
    connect(right_arrow, &QPushButton::pressed, file_encoding_transform_drag_in,
            &FileEncodingTransformDragIn::beginSend);
    connect(file_encoding_transform_drag_in, &FileEncodingTransformDragIn::sendFileList, this,
            &FileEncodingTransformMain::transformFiles);
    connect(this, &FileEncodingTransformMain::sendTransformedFile, file_encoding_transform_result,
            &FileEncodingTransformResult::receiveTransformedFile);
}

FileEncodingTransformMain::~FileEncodingTransformMain() {
    delete ui;
}

void FileEncodingTransformMain::transformFiles(QStringListModel *fileListModel) {
    qDebug() << fileListModel->stringList();
    for (int i = 0; i < fileListModel->rowCount(); i++) {
        qDebug() << fileListModel->data(fileListModel->index(i)).toString();
        QFile file(fileListModel->data(fileListModel->index(i)).toString());
        if (!file.open(QFile::ReadOnly |
                       QFile::Text)) {
            qDebug() << " Could not open the file for reading";
            return;
        }

        QTextStream in(&file);
        QString textString = in.readAll();
        qDebug() << textString;
        file.close();
        QTextCodec *codec = QTextCodec::codecForName("GB18030");
        QByteArray outputBytes = codec->fromUnicode(textString);
        QFileInfo oldFileInfo = QFileInfo(fileListModel->data(fileListModel->index(i)).toString());
        QString oldFilename = oldFileInfo.fileName();
        QDir oldFileDir = oldFileInfo.absoluteDir();
        QRegularExpression regex("^(.*)(\\..+)");
        qDebug() << oldFilename;
        qDebug() << oldFileDir;
        QString newFilename = oldFilename.replace(regex, "\\1_gbk\\2");
        QString newFilePath = oldFileDir.filePath(newFilename);
        QFile outputFile(newFilePath);
        if (!outputFile.open(QFile::WriteOnly)) {
            qDebug() << " Could not open the file for writing";
            return;
        }
        outputFile.write(outputBytes);
        outputFile.close();
        emit this->sendTransformedFile(newFilePath);
    }
}
