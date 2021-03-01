#include <QHBoxLayout>
#include "unhappy.h"
#include "./ui_unhappy.h"
#include "file_encoding_transform/file_encoding_transform_main.h"

Unhappy::Unhappy(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::unhappy)
{
    ui->setupUi(this);
    auto *main_layout = new QHBoxLayout(this);
    auto *file_encoding_transform_main = new FileEncodingTransformMain(this);
    main_layout->addWidget(file_encoding_transform_main);
    this->setLayout(main_layout);
}

Unhappy::~Unhappy()
{
    delete ui;
}

