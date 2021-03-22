//
// Created by 徐秋实 on 2021/3/22.
//

#ifndef UNHAPPY_EVOLUTION_PARSE_JSON_JSON_PLAIN_VIEWER_JSON_PLAIN_VIEWER_H_
#define UNHAPPY_EVOLUTION_PARSE_JSON_JSON_PLAIN_VIEWER_JSON_PLAIN_VIEWER_H_

#include <QPlainTextEdit>

namespace parse_json {
// json纯文本展示的预留结构
class JsonPlainViewer : public QPlainTextEdit {
  Q_OBJECT

  public:
    explicit JsonPlainViewer(QWidget *parent = nullptr);
    ~JsonPlainViewer() override;

};
}


#endif //UNHAPPY_EVOLUTION_PARSE_JSON_JSON_PLAIN_VIEWER_JSON_PLAIN_VIEWER_H_
