//
// Created by 徐秋实 on 2021/3/18.
//

// You may need to build the project (run Qt uic code generator) to get "ui_main_view.h" resolved
#include <QDebug>
#include <QJsonDocument>
#include <QMessageBox>
#include <QRegularExpression>
#include "main_view.h"
#include "ui_main_view.h"

parse_json::MainView::MainView(QWidget *parent) :
    QWidget(parent),
    ui_(new parse_json::Ui::MainView),
    json_viewer_(new parse_json::JsonPlainViewer(this)),
    main_tab_(new QTabWidget()),
    json_model_(new QJsonModel()),
    json_tree_(new QTreeView()) {
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
    QString raw_text = MainView::dealWithSingleQuote(this->ui_->raw_text->toPlainText());
    QJsonDocument json_doc = QJsonDocument::fromJson(raw_text.toUtf8());
    if (json_doc.isNull()) {
        QMessageBox::warning(this, "解析错误", "Failed to create JSON doc.");
        return;
    }
    this->formatted_stdout_json_ = json_doc.toJson(QJsonDocument::Indented);
    this->json_viewer_->setPlainText(this->formatted_stdout_json_);
    this->json_model_->loadJson(this->ui_->raw_text->toPlainText().toUtf8());
}

QString parse_json::MainView::dealWithSingleQuote(QString json_string) {
    bool need_transform = true;
    bool skip_current = false;
    int status = 0;  // 0 开始, 1 key start
    for (auto current_char : json_string) {
        if (skip_current) {
            skip_current = false;
            continue;
        }
        if (current_char == '\\') {
            skip_current = true;
            continue;
        }
        if (status == 0) {
            // 字符串开始
            if (current_char == '{') {
                // 如果遇到{则标记状态为key start
                status = 1;
            } else {
                // 其它情况直接略过
                continue;
            }
        } else {
            // key start
            if (current_char == ' ') {
                continue;
            } else if (current_char == '\'') {
                need_transform = true;
                break;
            } else {
                need_transform = false;
                break;
            }
        }
    }
    if (need_transform) {
        QRegularExpression regex("([^\\\\])'");
        json_string = json_string.replace(regex, "\\1\"");
    }
    return json_string;
}
