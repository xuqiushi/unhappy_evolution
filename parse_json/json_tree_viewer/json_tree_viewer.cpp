//
// Created by 徐秋实 on 2021/3/22.
//

// You may need to build the project (run Qt uic code generator) to get "ui_json_tree_viewer.h" resolved

#include "json_tree_viewer.h"

parse_json::JsonTreeViewer::JsonTreeViewer(QWidget *parent) :
    QTreeView(parent) {
}

parse_json::JsonTreeViewer::~JsonTreeViewer() {
}
