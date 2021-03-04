#ifndef UNHAPPY_EVOLUTION__UNHAPPY_H_
#define UNHAPPY_EVOLUTION__UNHAPPY_H_

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

QT_BEGIN_NAMESPACE
namespace Ui { class Unhappy; }
QT_END_NAMESPACE

enum ActivatePageId {
    TRANSFORM_ENCODING,
    PREVIEW_CSV
};

class Unhappy : public QWidget {
  Q_OBJECT

  public:
    explicit Unhappy(QWidget *parent = nullptr);
    ~Unhappy() override;

  private:
    Ui::Unhappy *ui_;
    QWidget *active_page_;
    QPushButton *file_encoding_transform_button_;
    QPushButton *preview_csv_button_;
    QVBoxLayout *main_layout_;

  private slots:
    void ChangeActivePage();
};
#endif // UNHAPPY_EVOLUTION__UNHAPPY_H_
