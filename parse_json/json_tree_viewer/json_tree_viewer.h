//
// Created by 徐秋实 on 2021/3/22.
//

#ifndef UNHAPPY_EVOLUTION_PARSE_JSON_JSON_TREE_VIEWER_JSON_TREE_VIEWER_H_
#define UNHAPPY_EVOLUTION_PARSE_JSON_JSON_TREE_VIEWER_JSON_TREE_VIEWER_H_

#include <QWidget>
#include <QTreeView>


namespace parse_json {
// 预留用来自定义tree view的结构
class JsonTreeViewer : public QTreeView {
  Q_OBJECT

  public:
    explicit JsonTreeViewer(QWidget *parent = nullptr);
    ~JsonTreeViewer() override;

};
}


#endif //UNHAPPY_EVOLUTION_PARSE_JSON_JSON_TREE_VIEWER_JSON_TREE_VIEWER_H_
