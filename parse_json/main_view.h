//
// Created by 徐秋实 on 2021/3/18.
//

#ifndef UNHAPPY_EVOLUTION_PARSE_JSON_MAIN_VIEW_H_
#define UNHAPPY_EVOLUTION_PARSE_JSON_MAIN_VIEW_H_

#include <QWidget>
#include <QTabWidget>
#include <QTreeView>
#include "parse_json/json_plain_viewer/json_plain_viewer.h"
#include "parse_json/json_tree_viewer/json_tree_model/json_tree_model.h"

QT_BEGIN_NAMESPACE
namespace parse_json::Ui {
class MainView;
}
QT_END_NAMESPACE

namespace parse_json {
class MainView : public QWidget {
  Q_OBJECT

  public:
    explicit MainView(QWidget *parent = nullptr);
    ~MainView() override;

  private slots:
    void startParse();

  private:
    parse_json::Ui::MainView *ui_;  // ui
    QString formatted_stdout_json_;  // 解析之后的json string
    QTabWidget *main_tab_;  // 主界面
    parse_json::JsonPlainViewer *json_viewer_;  // json纯文本预览
    QJsonModel *json_model_;  // json tree结构数据model
    QTreeView *json_tree_;  // json树结构预览

};
}

#endif //UNHAPPY_EVOLUTION_PARSE_JSON_MAIN_VIEW_H_
