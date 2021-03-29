//
// Created by 徐秋实 on 2021/3/25.
//

#ifndef UNHAPPY_EVOLUTION_RE_TEST_STRING_RAW_STRING_RAW_H_
#define UNHAPPY_EVOLUTION_RE_TEST_STRING_RAW_STRING_RAW_H_

#include <QWidget>
#include <QPlainTextEdit>

QT_BEGIN_NAMESPACE
namespace re_test::Ui { class StringRaw; }
QT_END_NAMESPACE

namespace re_test {
class StringRaw : public QPlainTextEdit {
  Q_OBJECT

  public:
    explicit StringRaw(QWidget *parent = nullptr);
    ~StringRaw() override;

  private:
    re_test::Ui::StringRaw *ui_;
};
}


#endif //UNHAPPY_EVOLUTION_RE_TEST_STRING_RAW_STRING_RAW_H_
