//
// Created by 徐秋实 on 2021/5/6.
//

// You may need to build the project (run Qt uic code generator) to get "ui_main_view.h" resolved
#include <QDebug>
#include <QString>
#include <QTextStream>
#include "code_snapshot/main_view.h"
#include "code_snapshot/ui_main_view.h"

code_snapshot::MainView::MainView(QWidget *parent) :
    QWidget(parent),
    ui_(new code_snapshot::Ui::MainView),
    main_layout_(new QHBoxLayout(this)),
    snap_viewer_(new SnapViewer(this)),
    snap_selector_(new SnapSelector(this)) {
    ui_->setupUi(this);

    this->setLayout(this->main_layout_);
    this->main_layout_->addWidget(this->snap_selector_, 2);
    this->main_layout_->addWidget(this->snap_viewer_, 8);
    connect(this->snap_selector_, &SnapSelector::emitSelectedName, this->snap_viewer_, &SnapViewer::changeRawSnap);
}

code_snapshot::MainView::~MainView() {
    delete ui_;
}

