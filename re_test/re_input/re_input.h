//
// Created by 徐秋实 on 2021/3/25.
//

#ifndef UNHAPPY_EVOLUTION_RE_TEST_RE_INPUT_RE_INPUT_H_
#define UNHAPPY_EVOLUTION_RE_TEST_RE_INPUT_RE_INPUT_H_

#include <QWidget>
#include <QLineEdit>

QT_BEGIN_NAMESPACE
namespace re_test::Ui { class ReInput; }
QT_END_NAMESPACE

namespace re_test {
class ReInput : public QLineEdit {
  Q_OBJECT

  public:
    explicit ReInput(QWidget *parent = nullptr);
    ~ReInput() override;

  private:
    re_test::Ui::ReInput *ui_;
};
}


#endif //UNHAPPY_EVOLUTION_RE_TEST_RE_INPUT_RE_INPUT_H_
