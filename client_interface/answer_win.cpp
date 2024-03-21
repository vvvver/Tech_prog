#include "answer_win.h"
#include "ui_answer_win.h"
//#include "test_win.h"

answer_win::answer_win(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::answer_win)
{
    ui->setupUi(this);
    setWindowTitle("Ответ");

}

answer_win::~answer_win()
{
    delete ui;
}

void answer_win::on_exit_butt_clicked()
{
    close();
}

void answer_win::on_cancel_butt_clicked()
{
    hide();
    emit openTest();
}

