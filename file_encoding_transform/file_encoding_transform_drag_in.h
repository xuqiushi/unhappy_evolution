//
// Created by 徐秋实 on 2021/2/23.
//

#ifndef UNHAPPY_EVOLUTION_FILE_ENCODING_TRANSFORM_DRAG_IN_H
#define UNHAPPY_EVOLUTION_FILE_ENCODING_TRANSFORM_DRAG_IN_H

#include <vector>
#include <QWidget>
#include <QMimeData>
#include <QStringListModel>

QT_BEGIN_NAMESPACE
namespace Ui { class FileEncodingTransformDragIn; }
QT_END_NAMESPACE

class FileEncodingTransformDragIn : public QWidget {
Q_OBJECT

public:
    explicit FileEncodingTransformDragIn(QWidget *parent = nullptr);

    ~FileEncodingTransformDragIn() override;

private:
    void dropEvent(QDropEvent *event) override;

    void dragEnterEvent(QDragEnterEvent *event) override;

    void dragLeaveEvent(QDragLeaveEvent *event) override;

public slots:
    void beginSend();

signals:
    void sendFileList(QStringListModel *fileListModel);

private:
    Ui::FileEncodingTransformDragIn *ui;
    QStringListModel *fileListModel = new QStringListModel();

};

#endif //UNHAPPY_EVOLUTION_FILE_ENCODING_TRANSFORM_DRAG_IN_H
