//
// Created by 徐秋实 on 2021/3/25.
//

#ifndef UNHAPPY_EVOLUTION_RE_TEST_MAIN_VIEW_H_
#define UNHAPPY_EVOLUTION_RE_TEST_MAIN_VIEW_H_

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QRegularExpression>
#include "re_test/re_input/re_input.h"
#include "re_test/string_raw/string_raw.h"
#include "re_test/string_match/string_match.h"

QT_BEGIN_NAMESPACE
namespace re_test::Ui { class MainView; }
QT_END_NAMESPACE

namespace re_test {
class MainView : public QWidget {
  Q_OBJECT

  public:
    explicit MainView(QWidget *parent = nullptr);
    ~MainView() override;

  private:
    Ui::MainView *ui_;
    QVBoxLayout *main_layout_;  // 整体layout为垂直
    QHBoxLayout *body_layout_;  // 下部layout为水平
    re_test::ReInput *re_input_;  // 输入正则表达式部分
    re_test::StringRaw *string_raw_;  // 输入原始字符串部分
    re_test::StringMatch *string_match_;  // 产生匹配结果部分
    QRegularExpression current_re_;  // 当前的正则表达式

  private slots:
    void reInputChanging();

  signals:
    void startHighlight(const QList<std::pair<int, int>>& highlight_intervals);
};
}

#endif //UNHAPPY_EVOLUTION_RE_TEST_MAIN_VIEW_H_
