//
// Created by 徐秋实 on 2021/5/7.
//

// You may need to build the project (run Qt uic code generator) to get "ui_snap_viewer.h" resolved
#include "snap_viewer.h"
#include "ui_snap_viewer.h"

namespace code_snapshot {
SnapViewer::SnapViewer(QWidget *parent) :
    QWidget(parent),
    main_layout_(new QVBoxLayout(this)),
    viewer_(new QPlainTextEdit(this)),
    replace_button_(new QPushButton("替换")),
    arg_layout_(new QHBoxLayout(this)),
    arg_edit_widgets_(QList<QLineEdit *>()),
    raw_snap_(QString("")),
    replaced_snap_(QString("")),
    ui_(new Ui::SnapViewer) {
    ui_->setupUi(this);
    this->setLayout(this->main_layout_);
    this->main_layout_->setAlignment(Qt::AlignTop);
    this->main_layout_->addWidget(this->replace_button_, 2);
    this->main_layout_->addLayout(this->arg_layout_, 0);
    this->main_layout_->addWidget(this->viewer_, 6);
    connect(this->replace_button_, &QPushButton::pressed, this, &SnapViewer::replaceSnap);
}

SnapViewer::~SnapViewer() {
    delete ui_;
}

void SnapViewer::changeRawSnap(const QString &raw_snap, const int &arg_count) {
    this->raw_snap_ = raw_snap;
    this->viewer_->setPlainText(this->raw_snap_);
    this->refreshArgEdit(arg_count);
}

void SnapViewer::refreshArgEdit(int arg_count) {
    this->arg_edit_widgets_.clear();
    // 删除arg_layout_下的所有项目
    QLayoutItem *item;
    while ((item = this->arg_layout_->takeAt(0))) {
        if (item->widget()) {
            item->widget()->setParent(nullptr);
        }
    }
    delete item;
    for (int i = 0; i < arg_count; i++) {
        auto *current_arg = new QLineEdit(QString("\%%1").arg(i + 1));
        this->arg_edit_widgets_.push_back(current_arg);
        this->arg_layout_->addWidget(current_arg);
    }
}
void SnapViewer::replaceSnap() {
    // 将原始snap用输入的字符串替换
    this->replaced_snap_ = this->raw_snap_;
    for (auto &arg_edit: this->arg_edit_widgets_) {
        this->replaced_snap_ = this->replaced_snap_.arg(arg_edit->text());
    }
    this->viewer_->setPlainText(this->replaced_snap_);
}

} // code_snapshot
