//
// Created by 徐秋实 on 2021/3/25.
//

// You may need to build the project (run Qt uic code generator) to get "ui_string_raw.h" resolved

#include "string_raw.h"
#include "re_test/string_raw/ui_string_raw.h"

re_test::StringRaw::StringRaw(QWidget *parent) :
    QPlainTextEdit(parent), ui_(new re_test::Ui::StringRaw) {
    ui_->setupUi(this);
}

re_test::StringRaw::~StringRaw() {
    delete ui_;
}
