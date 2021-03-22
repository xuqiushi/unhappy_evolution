//
// Created by 徐秋实 on 2021/3/22.
//

// You may need to build the project (run Qt uic code generator) to get "ui_json_viewer.h" resolved

#include "json_plain_viewer.h"

parse_json::JsonPlainViewer::JsonPlainViewer(QWidget *parent) :
    QPlainTextEdit(parent) {
}

parse_json::JsonPlainViewer::~JsonPlainViewer() {
}
