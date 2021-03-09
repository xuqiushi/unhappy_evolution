//
// Created by 徐秋实 on 2021/3/9.
//

#ifndef UNHAPPY_EVOLUTION_TOOLS_CSV_LINE_PARSER_H_
#define UNHAPPY_EVOLUTION_TOOLS_CSV_LINE_PARSER_H_
#include <QString>
#include <QStringList>
namespace tools {
class CsvLineParser {
  public:
    CsvLineParser(QString raw_line, QString line_sep);
    QStringList getParsedList();
  private:
    QString raw_line_;
    QString line_sep_;
};
}
#endif //UNHAPPY_EVOLUTION_TOOLS_CSV_LINE_PARSER_H_
