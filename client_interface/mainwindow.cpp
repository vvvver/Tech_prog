#include "mainwindow.h"
#include "dialog_reg.h"
#include "ui_mainwindow.h"
#include "test_win.h"
#include "func_for_client.h"
#include <QMessageBox>
//#include <QDebug>
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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_authButton_clicked()
{
    QString login = ui->lineEdit->text();
    QString password = ui->lineEdit_2->text();
    //MyClientSingleton::my_send_message(login +"&"+my_hash(password))
    if(login == "Vasya" && password == "qwerty123"){
        hide();
        test_win window;
        window.setModal(true);
        window.exec();
    } else {
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
