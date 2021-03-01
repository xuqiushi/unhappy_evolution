//
// Created by 徐秋实 on 2021/2/23.
//

#ifndef UNHAPPY_EVOLUTION_FILE_ENCODING_TRANSFORM_MAIN_H
#define UNHAPPY_EVOLUTION_FILE_ENCODING_TRANSFORM_MAIN_H

#include <QWidget>
#include <QStringListModel>

QT_BEGIN_NAMESPACE
namespace Ui { class FileEncodingTransformMain; }
QT_END_NAMESPACE

class FileEncodingTransformMain : public QWidget {
Q_OBJECT

public:
    explicit FileEncodingTransformMain(QWidget *parent = nullptr);

    ~FileEncodingTransformMain() override;

private slots:
    void transformFiles(QStringListModel *fileListModel);

signals:
    void sendTransformedFile(QString filePath);

private:
    Ui::FileEncodingTransformMain *ui;
    QStringListModel *transformFileModel;
};

#endif //UNHAPPY_EVOLUTION_FILE_ENCODING_TRANSFORM_MAIN_H
