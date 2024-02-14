#include "test_win.h"
#include "ui_test_win.h"

test_win::test_win(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::test_win)
{
    ui->setupUi(this);
}

test_win::~test_win()
{
    delete ui;
}
