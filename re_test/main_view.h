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
    QVBoxLayout *main_layout_;
    QHBoxLayout *body_layout_;
    re_test::ReInput *re_input_;
    re_test::StringRaw *string_raw_;
    re_test::StringMatch *string_match_;
    QRegularExpression current_re_;

  private slots:
    void reInputChanging();

  signals:
    void startHightlight(const QList<std::pair<int, int>>& highlight_intervals);
};
}

#endif //UNHAPPY_EVOLUTION_RE_TEST_MAIN_VIEW_H_
