//
// Created by 徐秋实 on 2021/3/4.
//

// You may need to build the project (run Qt uic code generator) to get "ui_main_view.h" resolved
#include <QVBoxLayout>
#include <QDebug>
#include <QPushButton>
#include "tools/csv_line_parser.h"
#include "main_view.h"
#include "preview_csv/ui_main_view.h"

preview_csv::MainView::MainView(QWidget *parent) :
    QWidget(parent),
    ui_(new Ui::MainView),
    main_tab_(new QTabWidget()),
    layout_(new QVBoxLayout()),
    file_path_line_(new preview_csv::FilePathGetter("拖拽文件至此")),
    preview_content_widget_(new preview_csv::PreviewContent()) {
    // 创建整个界面
    ui_->setupUi(this);
    // 创建垂直布局
    // 第一行保存文件路径
    this->file_path_line_ = new preview_csv::FilePathGetter("拖拽文件至此");
    this->file_path_line_->setDragEnabled(true);
    this->layout_->addWidget(this->file_path_line_, 1);
    // 分类型预览信息
    // 第一页放置预览表格内容
    this->preview_content_widget_ = new preview_csv::PreviewContent();
    this->main_tab_->addTab(this->preview_content_widget_, "预览内容");
    this->layout_->addWidget(this->main_tab_);
    this->setLayout(this->layout_);
    connect(this->file_path_line_,
            &preview_csv::FilePathGetter::emitFilePath,
            this->preview_content_widget_,
            &preview_csv::PreviewContent::receiveFilePath);
}

preview_csv::MainView::~MainView() {
    delete ui_;
    delete main_tab_;
    delete layout_;
    delete file_path_line_;
    delete preview_content_widget_;
}
