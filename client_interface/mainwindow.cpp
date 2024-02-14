#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "test_win.h"
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
}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_pushButton_clicked()
{
    QString login = ui->lineEdit->text();
    QString password = ui->lineEdit_2->text();
    if(login == "IvanII" && password == "qwerty123"){
        hide();
        test_win window;
        window.setModal(true);
        window.exec();
    } else {
        QMessageBox::warning(this, "Авторизация", "Вы не смогли авторизоваться");
    }
}

