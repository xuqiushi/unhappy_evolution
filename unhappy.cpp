#include <QVBoxLayout>
#include <QButtonGroup>
#include <QPushButton>
#include "unhappy.h"
#include "./ui_unhappy.h"
#include "file_encoding_transform/main_view.h"

Unhappy::Unhappy(QWidget *parent)
        : QWidget(parent), ui(new Ui::unhappy) {
    // 配置ui文件
    ui->setupUi(this);
    // 配置主布局为垂直布局
    auto *main_layout = new QVBoxLayout(this);
    // 主布局上半部分为选项
    auto *head_bar = new QFrame();
    head_bar->setFrameStyle(QFrame::StyledPanel | QFrame::Plain);
    auto *head_h_layout = new QHBoxLayout();
    auto *control_group = new QButtonGroup(head_h_layout);
    control_group->setExclusive(true);
    auto *transform_encoding_button = new QPushButton(QString("transform_encoding"));
    auto *preview_csv_button = new QPushButton(QString("preview_csv_button"));
    control_group->addButton(transform_encoding_button);
    control_group->addButton(preview_csv_button);
    head_h_layout->addWidget(transform_encoding_button);
    head_h_layout->addWidget(preview_csv_button);
    head_bar->setLayout(head_h_layout);
    // 主布局下半部分
    auto *h_layout = new QHBoxLayout();
    auto *file_encoding_transform_main = new file_encoding_transform::MainView(this);
    h_layout->addWidget(file_encoding_transform_main);
    // 分配主布局上下比例
    main_layout->addWidget(head_bar, 1);
    main_layout->addLayout(h_layout, 9);
    this->setLayout(main_layout);
}

Unhappy::~Unhappy() {
    delete ui;
}

