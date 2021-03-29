//
// Created by 徐秋实 on 2021/3/25.
//

// You may need to build the project (run Qt uic code generator) to get "ui_string_match.h" resolved

#include "string_match.h"
#include "re_test/string_match/ui_string_match.h"

re_test::StringMatch::StringMatch(QWidget *parent) :
    QPlainTextEdit(parent), ui_(new re_test::Ui::StringMatch) {
    this->color_circle_ = nullptr;
    ui_->setupUi(this);
    this->generateColorCircle();
}

re_test::StringMatch::~StringMatch() {
    delete ui_;
    this->cleanColorCircle();
}

void re_test::StringMatch::setHighlightMather(const QList<std::pair<int, int>> &highlight_intervals) {
    QList<QTextEdit::ExtraSelection> extra_selections;
    ColorCircleNode *current_color = this->color_circle_;
    if (!isReadOnly()) {
        for (auto interval: highlight_intervals) {
            QTextEdit::ExtraSelection selection;

            QColor line_color = current_color->color;
            current_color = current_color->next;

            selection.format.setBackground(line_color);
//            selection.format.setProperty(QTextFormat::FullWidthSelection, true);
            selection.cursor = this->textCursor();
            selection.cursor.setPosition(interval.first, QTextCursor::MoveAnchor);
            selection.cursor.setPosition(interval.second, QTextCursor::KeepAnchor);
            extra_selections.append(selection);
        }
    }
    setExtraSelections(extra_selections);
}

void re_test::StringMatch::generateColorCircle() {
    QList<QColor> color_list = QList<QColor>{
        QColor(Qt::red).lighter(160),
        QColor(Qt::yellow).lighter(160),
        QColor(Qt::blue).lighter(160)
    };
    this->color_circle_ = new ColorCircleNode;
    this->color_circle_->color = color_list[0];
    ColorCircleNode *current_node = this->color_circle_;
    for (int i=1; i<color_list.size(); i++) {
        auto *new_node = new ColorCircleNode;
        new_node->color = color_list[i];
        current_node->next = new_node;
        current_node = new_node;
    }
    current_node->next = this->color_circle_;
}

void re_test::StringMatch::cleanColorCircle() {

    ColorCircleNode *current_node = this->color_circle_->next;
    ColorCircleNode *last_node;
    while(current_node != this->color_circle_) {
       last_node = current_node;
       current_node = current_node->next;
       delete last_node;
    }
    delete current_node;
}