
#include "ui_mainwindow.h"
#include "func_for_client.h"
#include "mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Авторизация");

    ui->lineEdit->setPlaceholderText("Логин");
    ui->lineEdit_2->setPlaceholderText("Пароль");

    ui->lineEdit->setClearButtonEnabled(true);
    ui->lineEdit_2->setClearButtonEnabled(true);

    ui->lineEdit_2->setEchoMode(QLineEdit::Password);

    window = new Dialog_reg();
    connect(window, &Dialog_reg::openMain, this, &MainWindow::show);

    nav_win = new Navigation_page();

    connect(this, &MainWindow::open_nav, nav_win, &Navigation_page::show);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_authButton_clicked()
{
    QString login = ui->lineEdit->text();
    QString password = ui->lineEdit_2->text();
    if(auth(login,password)){
        nav_win->userLog = login;
        this->close();
        emit open_nav();

    }
    else {
        ui->lineEdit->clear();
        ui->lineEdit_2->clear();
        QMessageBox::warning(this, "Авторизация", "Вы не смогли авторизоваться");
    }
}



void MainWindow::on_regButton_clicked()
{
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    window->show();
    this->close();
}
