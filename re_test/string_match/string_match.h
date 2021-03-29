//
// Created by 徐秋实 on 2021/3/25.
//

#ifndef UNHAPPY_EVOLUTION_RE_TEST_STRING_MATCH_STRING_MATCH_H_
#define UNHAPPY_EVOLUTION_RE_TEST_STRING_MATCH_STRING_MATCH_H_

#include <QWidget>
#include <QPlainTextEdit>

QT_BEGIN_NAMESPACE
namespace re_test::Ui { class StringMatch; }
QT_END_NAMESPACE

namespace re_test {

struct ColorCircleNode {
    QColor color;
    ColorCircleNode *next;
};

class StringMatch : public QPlainTextEdit {
  Q_OBJECT

  public:
    explicit StringMatch(QWidget *parent = nullptr);
    ~StringMatch() override;

  private:
    re_test::Ui::StringMatch *ui_;
    ColorCircleNode *color_circle_;

  private:
    void generateColorCircle();
    void cleanColorCircle();

  public slots:
    void setHighlightMather(const QList<std::pair<int, int>>& highlight_intervals);
};
}


#endif //UNHAPPY_EVOLUTION_RE_TEST_STRING_MATCH_STRING_MATCH_H_
