//
// Created by 徐秋实 on 2021/5/7.
//

#ifndef UNHAPPY_EVOLUTION_CODE_SNAPSHOT_SNAP_SELECTOR_SNAP_SELECTOR_H_
#define UNHAPPY_EVOLUTION_CODE_SNAPSHOT_SNAP_SELECTOR_SNAP_SELECTOR_H_

#include <QWidget>
#include <QVBoxLayout>
#include <QComboBox>
#include <QListWidget>
#include "code_snapshot/snap_linker/snap_linker.h"

namespace code_snapshot {
QT_BEGIN_NAMESPACE
namespace Ui { class SnapSelector; }
QT_END_NAMESPACE

class SnapSelector : public QWidget {
  Q_OBJECT

  public:
    explicit SnapSelector(QWidget *parent = nullptr);
    ~SnapSelector() override;

  private:
    Ui::SnapSelector *ui_;
    QVBoxLayout *v_main_layout_;  // 总体为垂直，上方选择code类型
    QComboBox *language_types_;  // 语言类型选择
    QListWidget *snap_names_;  // snap名字
    SnapLinker *snap_linker_;  // 关联的所有snap索引

  private slots:
    void changeLanguage();
    void changeSnap(const QString &selected_name);

  signals:
    void emitSelectedName(const QString &selected_name, const int &arg_count);
};
} // code_snapshot

#endif //UNHAPPY_EVOLUTION_CODE_SNAPSHOT_SNAP_SELECTOR_SNAP_SELECTOR_H_
