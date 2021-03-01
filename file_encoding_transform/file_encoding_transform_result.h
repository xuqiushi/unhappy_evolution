//
// Created by 徐秋实 on 2021/2/23.
//

#ifndef UNHAPPY_EVOLUTION_FILE_ENCODING_TRANSFORM_RESULT_H
#define UNHAPPY_EVOLUTION_FILE_ENCODING_TRANSFORM_RESULT_H

#include <QWidget>
#include <QStringListModel>

QT_BEGIN_NAMESPACE
namespace Ui { class FileEncodingTransformResult; }
QT_END_NAMESPACE

class FileEncodingTransformResult : public QWidget {
Q_OBJECT

public:
    explicit FileEncodingTransformResult(QWidget *parent = nullptr);

    ~FileEncodingTransformResult() override;

private:
    Ui::FileEncodingTransformResult *ui;
    QStringListModel *transformedFileModel = new QStringListModel();

public slots:
    void receiveTransformedFile(const QString& transformedFilePath);
};

#endif //UNHAPPY_EVOLUTION_FILE_ENCODING_TRANSFORM_RESULT_H
