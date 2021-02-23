#include "unhappy.h"
#include "./ui_unhappy.h"

unhappy::unhappy(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::unhappy)
{
    ui->setupUi(this);
}

unhappy::~unhappy()
{
    delete ui;
}

