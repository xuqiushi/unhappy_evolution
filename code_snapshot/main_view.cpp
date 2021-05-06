//
// Created by 徐秋实 on 2021/5/6.
//

// You may need to build the project (run Qt uic code generator) to get "ui_main_view.h" resolved

#include "code_snapshot/main_view.h"
#include "code_snapshot/ui_main_view.h"

code_snapshot::MainView::MainView(QWidget *parent) :
    QWidget(parent), ui_(new code_snapshot::Ui::MainView) {
    ui_->setupUi(this);
}

code_snapshot::MainView::~MainView() {
    delete ui_;
}

