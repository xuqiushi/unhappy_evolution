#ifndef UNHAPPY_H
#define UNHAPPY_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class unhappy; }
QT_END_NAMESPACE

class unhappy : public QWidget
{
    Q_OBJECT

public:
    unhappy(QWidget *parent = nullptr);
    ~unhappy();

private:
    Ui::unhappy *ui;
};
#endif // UNHAPPY_H
