#include "navigation_page.h"
#include "ui_navigation_page.h"
#include "func_for_client.h"
#include <QMessageBox>

Navigation_page::Navigation_page(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Navigation_page)
{
    ui->setupUi(this);

    ui->stackedWidget->setCurrentIndex(0);
}

Navigation_page::~Navigation_page()
{
    delete ui;
}

void Navigation_page::on_task1_Button_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void Navigation_page::on_exit1_Button_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void Navigation_page::on_task2_Button_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void Navigation_page::on_exit_home_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void Navigation_page::on_exitButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void Navigation_page::on_stat_Button_clicked()
{
    QString login = "Vasya";
    //if(Statistics(login)){
        ui->stackedWidget->setCurrentIndex(1);
    //}
}


void Navigation_page::on_exit_Button_clicked()
{
    close();
}


void Navigation_page::on_submit_task1_button_clicked()
{
    QString variant = "12";
    QString answer = ui->answer_task1->text();

    if(Submit_task1("task_1", variant, answer)){
        ui->stackedWidget->setCurrentIndex(0);
    }
    else {
        ui->answer_task1->clear();
        QMessageBox::warning(this, "Ошибка", "Неправильный ответ");
    }
}


void Navigation_page::on_submit_task2_Button_clicked()
{
    QString variant = "12";
    QString answer = ui->answer_2->text();

    if(Submit_task1("task_2", variant, answer)){
        ui->stackedWidget->setCurrentIndex(0);
    }
    else {
        ui->answer_task1->clear();
        QMessageBox::warning(this, "Ошибка", "Неправильный ответ");
    }
}



