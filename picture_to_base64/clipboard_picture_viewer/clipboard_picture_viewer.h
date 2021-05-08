//
// Created by 徐秋实 on 2021/3/23.
//

#ifndef UNHAPPY_EVOLUTION_PICTURE_TO_BASE64_CLIPBOARD_PICTURE_VIEWER_CLIPBOARD_PICTURE_VIEWER_H_
#define UNHAPPY_EVOLUTION_PICTURE_TO_BASE64_CLIPBOARD_PICTURE_VIEWER_CLIPBOARD_PICTURE_VIEWER_H_

#include <QWidget>
#include <QLabel>
#include <QKeyEvent>

namespace picture_to_base64 {
class ClipboardPictureViewer : public QLabel {
  Q_OBJECT

  public:
    explicit ClipboardPictureViewer(QWidget *parent = nullptr);
    ~ClipboardPictureViewer() override;

  private:
    void keyPressEvent(QKeyEvent *ev) override;

  private:
    QImage *image_data_;

  public slots:
    void startSendImageForSave();

  signals:
    void sendBase64(QString image_base_64);
    void sendImageForSave(QImage * image);
};
}

#endif //UNHAPPY_EVOLUTION_PICTURE_TO_BASE64_CLIPBOARD_PICTURE_VIEWER_CLIPBOARD_PICTURE_VIEWER_H_
