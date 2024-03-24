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
    void openMain();

private slots:
    void on_createBut_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Dialog_reg *ui;

};

#endif // DIALOG_REG_H
