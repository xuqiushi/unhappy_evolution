//
// Created by 徐秋实 on 2021/3/5.
//

#ifndef UNHAPPY_EVOLUTION_PREVIEW_CSV_PARSE_OPTION_PARSE_OPTION_H_
#define UNHAPPY_EVOLUTION_PREVIEW_CSV_PARSE_OPTION_PARSE_OPTION_H_

#include <QWidget>
#include <QComboBox>

QT_BEGIN_NAMESPACE
namespace Ui { class ParseOption; }
QT_END_NAMESPACE

namespace preview_csv {
class ParseOption : public QWidget {
  Q_OBJECT

  public:
    explicit ParseOption(QWidget *parent = nullptr);
    ~ParseOption() override;

  signals:
    void sendInfo(int start_line, int end_line, QString line_sep);

  public slots:
    void sendParseInfo();

  private:
    Ui::ParseOption *ui_;
    QLineEdit *start_line_;  // 开始行
    QLineEdit *end_line_;  // 结束行
    QComboBox *line_sep_;  // csv sep值
    QRegExpValidator *line_reg_validator_;  // 用来做正则验证输入的数据的验证器
};
}

#endif //UNHAPPY_EVOLUTION_PREVIEW_CSV_PARSE_OPTION_PARSE_OPTION_H_
