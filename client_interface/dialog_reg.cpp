#include "dialog_reg.h"
#include "ui_dialog_reg.h"
#include "singletonclient.h"
//#include "mainwindow.h"
#include <QMessageBox>

Dialog_reg::Dialog_reg(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog_reg)
{
    ui->setupUi(this);
    setWindowTitle("Регистрация");

    ui->username->setPlaceholderText("Имя пользователя");
    ui->email_reg->setPlaceholderText("Адрес электронной почты");
    ui->password->setPlaceholderText("Пароль");

    ui->username->setClearButtonEnabled(true);
    ui->email_reg->setClearButtonEnabled(true);
    ui->password->setClearButtonEnabled(true);

    ui->password->setEchoMode(QLineEdit::Password);
}

Dialog_reg::~Dialog_reg()
{
    delete ui;
}

void Dialog_reg::on_createBut_clicked()
{
    QString username = ui ->username->text();
    QString pass = ui->password->text();
    QString mail = ui->email_reg->text();
    SingletonClient::getInstance()->seng_msg_to_server("reg&");
    SingletonClient::getInstance()->seng_msg_to_server(username + "&"
                                                       + pass + "&" + mail);
    hide();
    ui->username->clear();
    ui->password->clear();
    ui->email_reg->clear();
    emit openMain();
}


void Dialog_reg::on_pushButton_2_clicked()
{
    hide();
    ui->username->clear();
    ui->password->clear();
    ui->email_reg->clear();
    emit openMain();
}


