//
// Created by 徐秋实 on 2021/5/7.
//

// You may need to build the project (run Qt uic code generator) to get "ui_snap_selector.h" resolved

#include "snap_selector.h"

#include "ui_snap_selector.h"

namespace code_snapshot {
SnapSelector::SnapSelector(QWidget *parent) :
    QWidget(parent),
    ui_(new Ui::SnapSelector),
    v_main_layout_(new QVBoxLayout()),
    language_types_(new QComboBox(this)),
    snap_names_(new QListWidget(this)),
    snap_linker_(new SnapLinker()) {
    ui_->setupUi(this);
    this->setLayout(this->v_main_layout_);
    this->v_main_layout_->addWidget(this->language_types_, 2);
    this->v_main_layout_->addWidget(this->snap_names_, 8);
    this->v_main_layout_->setAlignment(Qt::AlignTop);
    this->language_types_->addItems(this->snap_linker_->getAllLanguageTypes());
    this->changeLanguage();
    connect(this->language_types_, &QComboBox::currentTextChanged, this, &code_snapshot::SnapSelector::changeLanguage);
    connect(this->snap_names_, &QListWidget::currentTextChanged, this, &SnapSelector::changeSnap);
}

SnapSelector::~SnapSelector() {
    delete ui_;
    delete this->snap_linker_;
}

void SnapSelector::changeSnap(const QString &selected_name) {
    // 更换snap
    QString raw_snap = this->snap_linker_->getRawSnapshot(this->language_types_->currentText(), selected_name);
    int arg_count = this->snap_linker_->getArgCount(this->language_types_->currentText(), selected_name);
    emit this->emitSelectedName(raw_snap, arg_count);
}

void SnapSelector::changeLanguage() {
    // 更换语言
    this->snap_names_->clear();
    const QString &language = this->language_types_->currentText();
    for (const auto &snap_name: snap_linker_->getAllSnapNamesByLanguageType(language)) {
        this->snap_names_->addItem(
            new QListWidgetItem(tr(snap_name.toStdString().c_str()), this->snap_names_)
        );
    }
}


} // code_snapshot
