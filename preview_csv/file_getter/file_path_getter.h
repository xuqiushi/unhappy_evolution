//
// Created by 徐秋实 on 2021/3/4.
//

#ifndef UNHAPPY_EVOLUTION_PREVIEW_CSV_FILE_GETTER_FILE_PATH_GETTER_H_
#define UNHAPPY_EVOLUTION_PREVIEW_CSV_FILE_GETTER_FILE_PATH_GETTER_H_

#include <QWidget>
#include <QLineEdit>

namespace preview_csv {
class FilePathGetter : public QLineEdit {
  Q_OBJECT
  private:
    QString file_path_;  // 文件路径

  public:
    explicit FilePathGetter(const QString &text);
    ~FilePathGetter() override;

  private:
    void dropEvent(QDropEvent *event) override;  // 拖拽的放置event

    void dragEnterEvent(QDragEnterEvent *event) override;  // 拖拽的进入范围event

    void dragLeaveEvent(QDragLeaveEvent *event) override;  // 拖拽的离开范围event

  signals:
    void emitFilePath(QString file_path);  // 发送文件路径signal
};
}

#endif //UNHAPPY_EVOLUTION_PREVIEW_CSV_FILE_GETTER_FILE_PATH_GETTER_H_
