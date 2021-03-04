//
// Created by 徐秋实 on 2021/2/23.
//

#ifndef UNHAPPY_EVOLUTION_FILE_ENCODING_TRANSFORM_RESULT_VIEW_H_
#define UNHAPPY_EVOLUTION_FILE_ENCODING_TRANSFORM_RESULT_VIEW_H_

#include <QWidget>
#include <QStringListModel>

QT_BEGIN_NAMESPACE
namespace Ui { class ResultView; }
QT_END_NAMESPACE

namespace file_encoding_transform {
class ResultView : public QWidget {
  Q_OBJECT

  public:
    explicit ResultView(QWidget *parent = nullptr);

    ~ResultView() override;

  private:
    Ui::ResultView *ui_;
    QStringListModel *transformed_file_model_ = new QStringListModel();

  public slots:
    void ReceiveTransformedFile(const QString &transformed_file_path);
};
}

#endif //UNHAPPY_EVOLUTION_FILE_ENCODING_TRANSFORM_RESULT_VIEW_H_
