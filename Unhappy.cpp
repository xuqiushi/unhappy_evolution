
#include "Unhappy.h"
#include "./ui_unhappy.h"

Unhappy::Unhappy(QWidget *parent)
    : QWidget(parent),
      ui_(new Ui::Unhappy),
      main_layout_(new QVBoxLayout()),
      head_bar_(new QFrame()),
      head_h_layout_(new QHBoxLayout()),
      button_map_(
          std::map<GlobalFuncType, QPushButton *>{
              {PARSE_JSON, new QPushButton(QString("json解析"))},
              {FILE_ENCODING_TRANSFORM, new QPushButton(QString("文件UTF-8转GB18030"))},
              {FAST_PREVIEW_CSV, new QPushButton(QString("快速预览csv"))},
              {PICTURE_TO_BASE_64, new QPushButton(QString("剪切板转base64"))},
              {RE_TEST, new QPushButton(QString("正则测试"))}
          }
      ),
      function_map_(
          std::map<GlobalFuncType, QWidget *>{
              {PARSE_JSON, new parse_json::MainView(this)},
              {FILE_ENCODING_TRANSFORM, new file_encoding_transform::MainView(this)},
              {FAST_PREVIEW_CSV, new preview_csv::MainView(this)},
              {PICTURE_TO_BASE_64, new picture_to_base64::MainView(this)},
              {RE_TEST, new re_test::MainView(this)}
          }
      ) {
    // 配置ui文件
    ui_->setupUi(this);
    // 创建第一行导航按钮
    this->control_group_ = new QButtonGroup(this->head_h_layout_);
    for (auto &button : this->button_map_) {
        button.second->setFocusPolicy(Qt::NoFocus);
        this->control_group_->addButton(button.second);
        // 主布局上半部分为选项
        this->head_h_layout_->addWidget(button.second);
        // 主布局下半部分通过点击按钮进行变化
        connect(button.second, &QPushButton::pressed, this, &Unhappy::changeActivePage);
        // 添加按钮与key反向关联
        this->reversed_button_map_.insert(
            std::make_pair(button.second, button.first)
        );
        // 隐藏content部分
        this->function_map_.find(button.first)->second->hide();
    }
    // 显示默认激活的页面
    this->active_page_ = this->function_map_.find(RE_TEST)->second;
    this->active_page_->show();
    this->head_bar_->setFrameStyle(QFrame::StyledPanel | QFrame::Plain);
    this->control_group_->setExclusive(true);
    this->head_bar_->setLayout(this->head_h_layout_);
    // 分配主布局上下比例
    this->main_layout_->addWidget(this->head_bar_, 1);
    this->main_layout_->addWidget(this->active_page_, 9);
    this->setLayout(this->main_layout_);
}

Unhappy::~Unhappy() {
    delete ui_;
    delete main_layout_;
}

void Unhappy::changeActivePage() {
    QWidget *tmp;  // 保存现在激活的widget
    QObject *button = QObject::sender();  // 获取传信号button指针
    tmp = this->active_page_;
    // 关闭现在这个widget
    tmp->hide();
    this->active_page_ = this->function_map_.find(this->reversed_button_map_.find(button)->second)->second;
    // 替换现在的widget为需要激活的widget
    this->active_page_->show();
    this->main_layout_->replaceWidget(tmp, this->active_page_);

}

