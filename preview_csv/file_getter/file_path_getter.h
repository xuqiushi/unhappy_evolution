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
    QString file_path_;

  public:
    explicit FilePathGetter(const QString &text);
    ~FilePathGetter() override;

  private:
    void dropEvent(QDropEvent *event) override;

    void dragEnterEvent(QDragEnterEvent *event) override;

    void dragLeaveEvent(QDragLeaveEvent *event) override;

  signals:
    void emitFilePath(QString file_path);
};
}

#endif //UNHAPPY_EVOLUTION_PREVIEW_CSV_FILE_GETTER_FILE_PATH_GETTER_H_
