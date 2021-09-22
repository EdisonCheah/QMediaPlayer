#include "empty.h"
#include "ui_empty.h"
#include "dialog.h"

Empty::Empty(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Empty)
{
    ui->setupUi(this);
}

Empty::~Empty()
{
    delete ui;
}

void Empty::on_pushButton_clicked()
{
    close();
}

