#ifndef UNHAPPY_H
#define UNHAPPY_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class unhappy; }
QT_END_NAMESPACE

enum ActivatePageId {
  transform_encoding
};

class Unhappy : public QWidget {
 Q_OBJECT

 public:
  Unhappy(QWidget *parent = nullptr);
  ~Unhappy();

 private:
  Ui::unhappy *ui;
  QWidget activePage;
};
#endif // UNHAPPY_H
