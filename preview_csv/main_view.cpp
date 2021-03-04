//
// Created by 徐秋实 on 2021/3/4.
//

// You may need to build the project (run Qt uic code generator) to get "ui_main_view.h" resolved

#include "main_view.h"
#include "preview_csv/ui_main_view.h"

preview_csv::MainView::MainView(QWidget *parent) :
    QWidget(parent), ui_(new Ui::MainView) {
    ui_->setupUi(this);
}

preview_csv::MainView::~MainView() {
    delete ui_;
}
