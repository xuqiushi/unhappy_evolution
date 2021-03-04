//
// Created by 徐秋实 on 2021/2/23.
//

#ifndef UNHAPPY_EVOLUTION_FILE_ENCODING_TRANSFORM_DRAG_IN_H_
#define UNHAPPY_EVOLUTION_FILE_ENCODING_TRANSFORM_DRAG_IN_H_

#include <vector>
#include <QWidget>
#include <QMimeData>
#include <QStringListModel>

QT_BEGIN_NAMESPACE
namespace Ui { class FileEncodingTransformDragIn; }
QT_END_NAMESPACE

namespace file_encoding_transform {
class DragIn : public QWidget {
  Q_OBJECT

  public:
    explicit DragIn(QWidget *parent = nullptr);

    ~DragIn() override;

  private:
    void dropEvent(QDropEvent *event) override;

    void dragEnterEvent(QDragEnterEvent *event) override;

    void dragLeaveEvent(QDragLeaveEvent *event) override;

  public slots:
    void BeginSend();

  signals:
    void SendFileList(QStringListModel *file_list_model);

  private:
    Ui::FileEncodingTransformDragIn *ui_;
    QStringListModel *file_list_model_ = new QStringListModel();
};
}

#endif //UNHAPPY_EVOLUTION_FILE_ENCODING_TRANSFORM_DRAG_IN_H_
