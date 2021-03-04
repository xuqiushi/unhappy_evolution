//
// Created by 徐秋实 on 2021/3/4.
//

#ifndef UNHAPPY_EVOLUTION_PREVIEW_CSV_MAIN_VIEW_H_
#define UNHAPPY_EVOLUTION_PREVIEW_CSV_MAIN_VIEW_H_

#include <QWidget>
#include <QTableView>
#include <QStandardItemModel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainView; }
QT_END_NAMESPACE

namespace preview_csv {
class MainView : public QWidget {
  Q_OBJECT

  public:
    explicit MainView(QWidget *parent = nullptr);
    ~MainView() override;

  private slots:
    void getFileInfo(const QString& file_path);

  private:
    Ui::MainView *ui_;
    QTableView *table_view_;
    QStandardItemModel *table_data_;
};
}

#endif //UNHAPPY_EVOLUTION_PREVIEW_CSV_MAIN_VIEW_H_
