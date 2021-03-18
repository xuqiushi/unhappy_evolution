
#include "Unhappy.h"
#include "./ui_unhappy.h"

Unhappy::Unhappy(QWidget *parent)
    : QWidget(parent),
      ui_(new Ui::Unhappy),
      main_layout_(new QVBoxLayout()),
      head_bar_(new QFrame()),
      head_h_layout_(new QHBoxLayout()),
      file_encoding_transform_button_(new QPushButton(QString("transform_encoding"))),
      preview_csv_button_(new QPushButton(QString("preview_csv_button"))),
      file_encoding_transform_(new file_encoding_transform::MainView(this)),
      preview_csv_(new preview_csv::MainView(this))
      {
    // 配置ui文件
    ui_->setupUi(this);
    // 创建第一行导航按钮
    this->file_encoding_transform_button_->setFocusPolicy(Qt::NoFocus);
    this->preview_csv_button_->setFocusPolicy(Qt::NoFocus);
    this->control_group_ = new QButtonGroup(this->head_h_layout_);
    // 隐藏content部分
    this->file_encoding_transform_->hide();
    this->preview_csv_->hide();
    // 显示默认激活的页面
    this->active_page_ = this->preview_csv_;
    this->active_page_->show();
    // 配置主布局为垂直布局
    // 主布局上半部分为选项
    this->head_bar_->setFrameStyle(QFrame::StyledPanel | QFrame::Plain);
    this->control_group_->setExclusive(true);
    this->control_group_->addButton(this->file_encoding_transform_button_);
    this->control_group_->addButton(this->preview_csv_button_);
    this->head_h_layout_->addWidget(this->file_encoding_transform_button_);
    this->head_h_layout_->addWidget(this->preview_csv_button_);
    this->head_bar_->setLayout(this->head_h_layout_);
    // 主布局下半部分通过点击按钮进行变化
    connect(this->file_encoding_transform_button_, &QPushButton::pressed, this, &Unhappy::changeActivePage);
    connect(this->preview_csv_button_, &QPushButton::pressed, this, &Unhappy::changeActivePage);
    // 分配主布局上下比例
    this->main_layout_->addWidget(this->head_bar_, 1);
    this->main_layout_->addWidget(this->active_page_, 9);
    this->setLayout(this->main_layout_);
}

Unhappy::~Unhappy() {
    delete ui_;
    delete main_layout_;
}

void Unhappy::changeActivePage() {
    QWidget *tmp;  // 保存现在激活的widget
    QObject *button = QObject::sender();  // 获取传信号button指针
    tmp = this->active_page_;
    // 关闭现在这个widget
    tmp->hide();
    if (button == this->file_encoding_transform_button_) {
        this->active_page_ = this->file_encoding_transform_;
    } else if (button == this->preview_csv_button_) {
        this->active_page_ = this->preview_csv_;
    }
    // 替换现在的widget为需要激活的widget
    this->active_page_->show();
    this->main_layout_->replaceWidget(tmp, this->active_page_);

}

