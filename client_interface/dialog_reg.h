#ifndef DIALOG_REG_H
#define DIALOG_REG_H

#include <QDialog>

namespace Ui {
class Dialog_reg;
}

class Dialog_reg : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_reg(QWidget *parent = nullptr);
    ~Dialog_reg();

signals:
    // \brief открытие главного окна
    void openMain();

private slots:
    // \brief слот создающий кнопку 1
    void on_createBut_clicked();

    // \brief слот реагирующий на нажатие кнопки 2
    void on_pushButton_2_clicked();

private:
    Ui::Dialog_reg *ui;

};

#endif // DIALOG_REG_H
