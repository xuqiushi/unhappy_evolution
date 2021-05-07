//
// Created by 徐秋实 on 2021/5/6.
//

#ifndef UNHAPPY_EVOLUTION_CODE_SNAPSHOT_MAIN_VIEW_H_
#define UNHAPPY_EVOLUTION_CODE_SNAPSHOT_MAIN_VIEW_H_

#include <QWidget>
#include <QHBoxLayout>
#include "code_snapshot/snap_selector/snap_selector.h"
#include "code_snapshot/snap_viewer/snap_viewer.h"

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
    QHBoxLayout *main_layout_;  // 主布局为水平
    SnapSelector *snap_selector_;  // 左侧选择snap部分
    SnapViewer *snap_viewer_;  // snap显示部分

};
}

#endif //UNHAPPY_EVOLUTION_CODE_SNAPSHOT_MAIN_VIEW_H_
