#include "navigation_page.h"
#include "ui_navigation_page.h"

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
    ui->stackedWidget->setCurrentIndex(1);
}


void Navigation_page::on_exit_Button_clicked()
{
    close();
}

