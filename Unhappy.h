#ifndef UNHAPPY_EVOLUTION__UNHAPPY_H_
#define UNHAPPY_EVOLUTION__UNHAPPY_H_

#include <QWidget>
#include <QButtonGroup>
#include <QPushButton>
#include <QVBoxLayout>
#include "file_encoding_transform/main_view.h"
#include "preview_csv/main_view.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Unhappy; }
QT_END_NAMESPACE

class Unhappy : public QWidget {
  Q_OBJECT

  public:
    explicit Unhappy(QWidget *parent = nullptr);
    ~Unhappy() override;

  private:
    Ui::Unhappy *ui_;
    QWidget *active_page_;
    QPushButton *file_encoding_transform_button_;
    QPushButton *preview_csv_button_;
    QVBoxLayout *main_layout_;  // 配置主布局为垂直布局
    QFrame *head_bar_;  // 上部主菜单
    QHBoxLayout *head_h_layout_;  // 上部菜单布局
    QButtonGroup *control_group_;  // 上部菜单按钮组
    file_encoding_transform::MainView *file_encoding_transform_;  // 文件转码部分
    preview_csv::MainView *preview_csv_;  // csv预览部分

  private slots:
    void changeActivePage();
};
#endif // UNHAPPY_EVOLUTION__UNHAPPY_H_
