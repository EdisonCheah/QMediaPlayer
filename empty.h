#ifndef EMPTY_H
#define EMPTY_H

#include <QDialog>

namespace Ui {
class Empty;
}

class Empty : public QDialog
{
    Q_OBJECT

public:
    explicit Empty(QWidget *parent = nullptr);
    ~Empty();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Empty *ui;
};

#endif // EMPTY_H
