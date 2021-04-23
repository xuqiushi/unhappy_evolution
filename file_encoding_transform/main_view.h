//
// Created by 徐秋实 on 2021/2/23.
//

#ifndef UNHAPPY_EVOLUTION_FILE_ENCODING_TRANSFORM_MAIN_VIEW_H_
#define UNHAPPY_EVOLUTION_FILE_ENCODING_TRANSFORM_MAIN_VIEW_H_

#include <QWidget>
#include <QStringListModel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainView; }
QT_END_NAMESPACE

namespace file_encoding_transform {
class MainView : public QWidget {
  Q_OBJECT

  public:
    explicit MainView(QWidget *parent = nullptr);

    ~MainView() override;

  private slots:
    void transformFiles(QStringListModel *file_list_model);

  signals:
    void sendTransformedFile(QString file_path);

  private:
    Ui::MainView *ui_;
};
}

#endif //UNHAPPY_EVOLUTION_FILE_ENCODING_TRANSFORM_MAIN_VIEW_H_
