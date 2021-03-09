//
// Created by 徐秋实 on 2021/3/9.
//

#include "csv_line_parser.h"

#include <utility>

tools::CsvLineParser::CsvLineParser(QString raw_line, QString line_sep)
    : raw_line_(std::move(raw_line)), line_sep_(std::move(line_sep)) {}

QStringList tools::CsvLineParser::getParsedList() {
    enum State { NORMAL, QUOTE } state = NORMAL;
    QStringList fields;
    QString value;

    for (int i = 0; i < this->raw_line_.size(); i++) {
        const QChar kCurrent = this->raw_line_.at(i);

        // Normal state
        if (state == NORMAL) {
            // Comma
            if (kCurrent == this->line_sep_) {
                // Save field
                fields.append(value.trimmed());
                value.clear();
            }

                // Double-quote
            else if (kCurrent == '"') {
                state = QUOTE;
                value += kCurrent;
            }

                // Other character
            else
                value += kCurrent;
        }

            // In-quote state state == QUOTE
        else {
            // Another double-quote
            if (kCurrent == '"') {
                if (i < this->raw_line_.size()) {
                    // A double double-quote?
                    if (i + 1 < this->raw_line_.size() && this->raw_line_.at(i + 1) == '"') {
                        value += '"';

                        // Skip a second quote character in a row
                        i++;
                    } else {
                        state = NORMAL;
                        value += '"';
                    }
                }
            }

                // Other character
            else
                value += kCurrent;
        }
    }

    if (!value.isEmpty())
        fields.append(value.trimmed());

    // Quotes are left in until here; so when fields are trimmed, only whitespace outside of
    // quotes is removed.  The quotes are removed here.
    for (int i = 0; i < fields.size(); ++i)
        if (fields[i].length() >= 1 && fields[i].left(1) == '"') {
            fields[i] = fields[i].mid(1);
            if (fields[i].length() >= 1 && fields[i].right(1) == '"')
                fields[i] = fields[i].left(fields[i].length() - 1);
        }

    return fields;
}