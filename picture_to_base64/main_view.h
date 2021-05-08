//
// Created by 徐秋实 on 2021/3/23.
//

#ifndef UNHAPPY_EVOLUTION_PICTURE_TO_BASE64_MAIN_VIEW_H_
#define UNHAPPY_EVOLUTION_PICTURE_TO_BASE64_MAIN_VIEW_H_

#include <QWidget>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QPushButton>
#include <QFileDialog>
#include "picture_to_base64/clipboard_picture_viewer/clipboard_picture_viewer.h"

QT_BEGIN_NAMESPACE
namespace picture_to_base64::Ui { class MainView; }
QT_END_NAMESPACE

namespace picture_to_base64{
class MainView : public QWidget {
  Q_OBJECT

  public:
    explicit MainView(QWidget *parent = nullptr);
    ~MainView() override;

  private:
    picture_to_base64::Ui::MainView *ui_;
    QVBoxLayout *main_layout_;
    picture_to_base64::ClipboardPictureViewer *clipboard_picture_viewer_;
    QPushButton *save_button_;
    QFileDialog *save_dialog_;
    QTextEdit *base_64_result_;

  private slots:
    void receiveBaseString(const QString& base_64_string);
    void saveImage(QImage *image);
};
}


#endif //UNHAPPY_EVOLUTION_PICTURE_TO_BASE64_MAIN_VIEW_H_
