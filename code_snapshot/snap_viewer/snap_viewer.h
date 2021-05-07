//
// Created by 徐秋实 on 2021/5/7.
//

#ifndef UNHAPPY_EVOLUTION_CODE_SNAPSHOT_SNAP_VIEWER_SNAP_VIEWER_H_
#define UNHAPPY_EVOLUTION_CODE_SNAPSHOT_SNAP_VIEWER_SNAP_VIEWER_H_

#include <QWidget>
#include <QList>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QVBoxLayout>

namespace code_snapshot {
QT_BEGIN_NAMESPACE
namespace Ui { class SnapViewer; }
QT_END_NAMESPACE

class SnapViewer : public QWidget {
  Q_OBJECT

  public:
    explicit SnapViewer(QWidget *parent = nullptr);
    ~SnapViewer() override;

  private:
    Ui::SnapViewer *ui_;
    QVBoxLayout *main_layout_;  // 显示主layout为垂直
    QPlainTextEdit *viewer_;  // 展示部分
    QPushButton *replace_button_;  // 替换按钮
    QHBoxLayout *arg_layout_;  // 需要替换的arg的layout，第二行
    QList<QLineEdit *> arg_edit_widgets_;  // 需要替换的arg具体的widget
    QString raw_snap_;  // 原始snap
    QString replaced_snap_;  // 替换后的snap

  private:
    void refreshArgEdit(int arg_count);

  public slots:
    void changeRawSnap(const QString &raw_snap, const int &arg_count);
    void replaceSnap();
};
} // code_snapshot

#endif //UNHAPPY_EVOLUTION_CODE_SNAPSHOT_SNAP_VIEWER_SNAP_VIEWER_H_
