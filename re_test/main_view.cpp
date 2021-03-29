//
// Created by 徐秋实 on 2021/3/25.
//

// You may need to build the project (run Qt uic code generator) to get "ui_main_view.h" resolved
#include <utility>
#include <QDebug>
#include <QRegularExpressionMatch>
#include "main_view.h"
#include "re_test/ui_main_view.h"

re_test::MainView::MainView(QWidget *parent) :
    QWidget(parent),
    ui_(new re_test::Ui::MainView),
    main_layout_(new QVBoxLayout()),
    body_layout_(new QHBoxLayout()),
    re_input_(new re_test::ReInput()),
    string_raw_(new re_test::StringRaw()),
    string_match_(new re_test::StringMatch()) {
    ui_->setupUi(this);
    this->setLayout(this->main_layout_);
    this->main_layout_->addWidget(this->re_input_);
    this->main_layout_->addLayout(this->body_layout_);
    this->body_layout_->addWidget(this->string_raw_);
    this->body_layout_->addWidget(this->string_match_);
    connect(this->re_input_, &re_test::ReInput::textChanged, this, &re_test::MainView::reInputChanging);
    connect(this, &re_test::MainView::startHightlight, this->string_match_, &re_test::StringMatch::setHighlightMather);
}

re_test::MainView::~MainView() {
    delete ui_;
}

void re_test::MainView::reInputChanging() {
    this->string_match_->setPlainText(this->string_raw_->toPlainText());
    this->current_re_.setPattern(this->re_input_->text());
    if (this->current_re_.isValid()) {
        QList<std::pair<int, int>> highlight_intervals;
        QRegularExpressionMatchIterator match_iterator = this->current_re_.globalMatch(this->string_raw_->toPlainText());
        QRegularExpressionMatch match;
        qDebug() << "____";
        while (match_iterator.hasNext()) {
            match = match_iterator.next();
            qDebug() << match.capturedStart() << match.capturedEnd();
            highlight_intervals.push_back(std::make_pair(match.capturedStart(), match.capturedEnd()));
        }
        emit this->startHightlight(highlight_intervals);
    }
}
