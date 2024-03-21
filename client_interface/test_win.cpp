#include "test_win.h"
#include "ui_test_win.h"
#include "answer_win.h"

test_win::test_win(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::test_win)
{
    ui->setupUi(this);
    setWindowTitle("Условие");

    window = new answer_win();
    connect(window, &answer_win::openTest, this, &test_win::show);
}

test_win::~test_win()
{
    delete ui;
}

void test_win::on_close_win_butt_clicked()
{
    close();
}


void test_win::on_view_answer_butt_clicked()
{
    hide();
    answer_win window;
    window.setModal(true);
    window.exec();

}

