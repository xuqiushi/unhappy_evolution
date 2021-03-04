#include <QButtonGroup>
#include <preview_csv/main_view.h>
#include "Unhappy.h"
#include "./ui_unhappy.h"
#include "file_encoding_transform/main_view.h"

Unhappy::Unhappy(QWidget *parent)
    : QWidget(parent), ui_(new Ui::Unhappy), active_page_(new preview_csv::MainView(this)) {
    // 配置ui文件
    ui_->setupUi(this);
    // 配置主布局为垂直布局
    this->main_layout_ = new QVBoxLayout();
    // 主布局上半部分为选项
    auto *head_bar = new QFrame();
    head_bar->setFrameStyle(QFrame::StyledPanel | QFrame::Plain);
    auto *head_h_layout = new QHBoxLayout();
    auto *control_group = new QButtonGroup(head_h_layout);
    control_group->setExclusive(true);
    this->file_encoding_transform_button_ = new QPushButton(QString("transform_encoding"));
    this->preview_csv_button_ = new QPushButton(QString("preview_csv_button"));
    control_group->addButton(this->file_encoding_transform_button_);
    control_group->addButton(this->preview_csv_button_);
    head_h_layout->addWidget(this->file_encoding_transform_button_);
    head_h_layout->addWidget(this->preview_csv_button_);
    head_bar->setLayout(head_h_layout);
    // 主布局下半部分通过点击按钮进行变化
    connect(this->file_encoding_transform_button_, &QPushButton::pressed, this, &Unhappy::ChangeActivePage);
    connect(this->preview_csv_button_, &QPushButton::pressed, this, &Unhappy::ChangeActivePage);
    // 分配主布局上下比例
    this->main_layout_->addWidget(head_bar, 1);
    this->main_layout_->addWidget(this->active_page_, 9);
    this->setLayout(this->main_layout_);
}

Unhappy::~Unhappy() {
    delete ui_;
}

void Unhappy::ChangeActivePage() {
    QWidget *tmp;  // 保存现在激活的widget
    QObject *button = QObject::sender();  // 获取传信号button指针
    tmp = this->active_page_;
    if (button == this->file_encoding_transform_button_) {
        this->active_page_ = new file_encoding_transform::MainView(this);
    } else if (button == this->preview_csv_button_) {
        this->active_page_ = new preview_csv::MainView(this);
    }
    // 替换现在的widget为需要激活的widget
    this->main_layout_->replaceWidget(tmp, this->active_page_);
    // 关闭现在这个widget
    tmp->close();
}

