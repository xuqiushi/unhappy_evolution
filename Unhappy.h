#ifndef UNHAPPY_EVOLUTION__UNHAPPY_H_
#define UNHAPPY_EVOLUTION__UNHAPPY_H_

#include <map>
#include <unordered_set>
#include <QWidget>
#include <QButtonGroup>
#include <QPushButton>
#include <QVBoxLayout>
#include "file_encoding_transform/main_view.h"
#include "preview_csv/main_view.h"
#include "parse_json/main_view.h"
#include "picture_to_base64/main_view.h"
#include "re_test/main_view.h"
#include "code_snapshot/main_view.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Unhappy; }
QT_END_NAMESPACE

enum GlobalFuncType {
    PARSE_JSON = 0x0,  // 解析json部分
    FILE_ENCODING_TRANSFORM = 0x1,  // 文件转码部分
    FAST_PREVIEW_CSV = 0x2,  // csv预览部分
    PICTURE_TO_BASE_64 = 0x3,  // 剪切板图片转base64
    RE_TEST = 0x4,  // 验证正则表达式
    CODE_SNAPSHOT = 0x5  // 代码片段
};

class Unhappy : public QWidget {
  Q_OBJECT

  public:
    explicit Unhappy(QWidget *parent = nullptr);
    ~Unhappy() override;

  private:
    Ui::Unhappy *ui_;
    QWidget *active_page_;
    std::map<GlobalFuncType, QPushButton *> button_map_;
    std::map<QObject *, GlobalFuncType> reversed_button_map_;
    std::map<GlobalFuncType, QWidget *> function_map_;
    QVBoxLayout *main_layout_;  // 配置主布局为垂直布局
    QFrame *head_bar_;  // 上部主菜单
    QHBoxLayout *head_h_layout_;  // 上部菜单布局
    QButtonGroup *control_group_;  // 上部菜单按钮组


  private slots:
    void changeActivePage();
};
#endif // UNHAPPY_EVOLUTION__UNHAPPY_H_
