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
    this->setReadOnly(true);
}

re_test::StringMatch::~StringMatch() {
    delete ui_;
    this->cleanColorCircle();
}

void re_test::StringMatch::setHighlightMather(const QList<std::pair<int, int>> &highlight_intervals) {
    // 自动选择区域
    QList<QTextEdit::ExtraSelection> extra_selections;
    // 取用颜色环起点颜色
    ColorCircleNode *current_color = this->color_circle_;
    for (auto interval: highlight_intervals) {
        // 遍历过程如果有起点等于终点直接跳过，放置颜色循环不正常
        if (interval.first == interval.second) {
            continue;
        }
        // 将当前区域的背景颜色设置一下
        QTextEdit::ExtraSelection selection;
        QColor line_color = current_color->color;
        current_color = current_color->next;
        selection.format.setBackground(line_color);
        selection.cursor = this->textCursor();
        selection.cursor.setPosition(interval.first, QTextCursor::MoveAnchor);
        selection.cursor.setPosition(interval.second, QTextCursor::KeepAnchor);
        extra_selections.append(selection);
    }
    setExtraSelections(extra_selections);
}

void re_test::StringMatch::generateColorCircle() {
    QList<QColor> color_list = QList<QColor>{
        QColor(Qt::red).lighter(160),
        QColor(Qt::yellow).lighter(160),
        QColor(Qt::blue).lighter(160)
    };
    // 初始化起始点
    this->color_circle_ = new ColorCircleNode;
    this->color_circle_->color = color_list[0];
    ColorCircleNode *current_node = this->color_circle_;
    for (int i = 1; i < color_list.size(); i++) {
        auto *new_node = new ColorCircleNode;
        new_node->color = color_list[i];
        current_node->next = new_node;
        current_node = new_node;
    }
    // 环尾部指向头部
    current_node->next = this->color_circle_;
}

void re_test::StringMatch::cleanColorCircle() {
    ColorCircleNode *current_node = this->color_circle_->next;
    ColorCircleNode *last_node;
    // 循环删除除了头结点之后节点
    while (current_node != this->color_circle_) {
        last_node = current_node;
        current_node = current_node->next;
        delete last_node;
    }
    // 删除头结点
    delete current_node;
}