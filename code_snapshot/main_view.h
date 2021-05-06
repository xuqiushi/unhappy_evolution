//
// Created by 徐秋实 on 2021/5/6.
//

#ifndef UNHAPPY_EVOLUTION_CODE_SNAPSHOT_MAIN_VIEW_H_
#define UNHAPPY_EVOLUTION_CODE_SNAPSHOT_MAIN_VIEW_H_

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace code_snapshot::Ui { class MainView; }
QT_END_NAMESPACE

namespace code_snapshot {
class MainView : public QWidget {
  Q_OBJECT

  public:
    explicit MainView(QWidget *parent = nullptr);
    ~MainView() override;

  private:
    Ui::MainView *ui_;
};
}

#endif //UNHAPPY_EVOLUTION_CODE_SNAPSHOT_MAIN_VIEW_H_
