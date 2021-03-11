//
// Created by 徐秋实 on 2021/3/4.
//

#ifndef UNHAPPY_EVOLUTION_PREVIEW_CSV_MAIN_VIEW_H_
#define UNHAPPY_EVOLUTION_PREVIEW_CSV_MAIN_VIEW_H_

#include <QWidget>
#include <QTableView>
#include <QStandardItemModel>
#include <QTableWidget>
#include "preview_csv/parse_option/parse_option.h"
#include "preview_csv/preview_content/preview_content.h"
#include "preview_csv/file_getter/file_path_getter.h"
#include "preview_csv/data_model/custom_csv_model.h"
#include "preview_csv/file_summary/file_summary.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainView; }
QT_END_NAMESPACE

namespace preview_csv {
class MainView : public QWidget {
  Q_OBJECT

  public:
    explicit MainView(QWidget *parent = nullptr);
    ~MainView() override;

  private:
    Ui::MainView *ui_;
    QTabWidget *main_tab_;  // 下方展示tab
    QVBoxLayout *layout_;  // 整体layout
    preview_csv::FilePathGetter *file_path_line_;  // 文件拖拽组件
    preview_csv::PreviewContent *preview_content_widget_;  // 预览表格组件
    preview_csv::FileSummary *file_summary_widget_;  // 预览表格组件

};
}

#endif //UNHAPPY_EVOLUTION_PREVIEW_CSV_MAIN_VIEW_H_
