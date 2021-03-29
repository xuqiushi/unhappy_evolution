//
// Created by 徐秋实 on 2021/3/25.
//

// You may need to build the project (run Qt uic code generator) to get "ui_re_input.h" resolved

#include "re_input.h"
#include "re_test/re_input/ui_re_input.h"

re_test::ReInput::ReInput(QWidget *parent) :
    QLineEdit(parent), ui_(new re_test::Ui::ReInput) {
    ui_->setupUi(this);
}

re_test::ReInput::~ReInput() {
    delete ui_;
}
