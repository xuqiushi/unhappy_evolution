//
// Created by 徐秋实 on 2021/3/18.
//

// You may need to build the project (run Qt uic code generator) to get "ui_main_view.h" resolved
#include <QDebug>
#include <QJsonDocument>
#include <QMessageBox>
#include "main_view.h"
#include "ui_main_view.h"

parse_json::MainView::MainView(QWidget *parent) :
    QWidget(parent),
    ui_(new parse_json::Ui::MainView),
    json_viewer_(new parse_json::JsonPlainViewer(this)),
    main_tab_(new QTabWidget()),
    json_model_(new QJsonModel()),
    json_tree_(new QTreeView()){
    ui_->setupUi(this);
    this->json_tree_->setModel(this->json_model_);
    // 解析按钮
    this->ui_->parse_layout->setAlignment(this->ui_->parse_button, Qt::AlignHCenter);
    // 纯文本与树结构的切换tab
    this->ui_->parse_layout->addWidget(this->main_tab_, 9);
    this->main_tab_->addTab(this->json_viewer_, "纯文本");
    this->main_tab_->addTab(this->json_tree_, "结构");
    // 树结构格子间的boarder style
    QString style = "QTreeView::item:!selected "
                    "{ "
                    "border: 1px solid gainsboro; "
                    "border-left: none; "
                    "border-top: none; "
                    "}"
                    "QTreeView::item:selected {}";
    this->json_tree_->setStyleSheet(style);
    connect(this->ui_->parse_button, &QPushButton::pressed, this, &parse_json::MainView::startParse);
}

parse_json::MainView::~MainView() {
    delete ui_;
}

void parse_json::MainView::startParse() {
    QJsonDocument json_doc = QJsonDocument::fromJson(this->ui_->raw_text->toPlainText().toUtf8());
    if (json_doc.isNull()) {
        QMessageBox::warning(this, "解析错误","Failed to create JSON doc.");
        return;
    }
    this->formatted_stdout_json_ = json_doc.toJson(QJsonDocument::Indented);
    this->json_viewer_->setPlainText(this->formatted_stdout_json_);
    this->json_model_->loadJson(this->ui_->raw_text->toPlainText().toUtf8());
}
