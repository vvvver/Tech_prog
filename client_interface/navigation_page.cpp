#include "navigation_page.h"
#include "ui_navigation_page.h"
#include "func_for_client.h"
#include "aes.h"
#include <QRandomGenerator>
#include <QDir>
#include <QMessageBox>
#include <QLabel>
//#include <QDebug>

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


    int randomInt = QRandomGenerator::global()->bounded(1, 3);
    QString query = Random_Graph(randomInt);
    graph = query;

    QString str = "C:/Users/abdua/Desktop/client_interface/png/"+
                  QString::number(randomInt) + ".png";
    QDir dir(str);
    QPixmap pix(str);

    int w = ui->label->width();
    int h = ui->label->height();
    ui->label->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));
    ui->label->show();

}
void Navigation_page::on_exit1_Button_clicked()
{
    ui->answer_task1->clear();
    ui->stackedWidget->setCurrentIndex(0);
}

void Navigation_page::on_task2_Button_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void Navigation_page::on_exit_home_clicked()
{
    ui->answer_2->clear();
    ui->stackedWidget->setCurrentIndex(0);
}


void Navigation_page::on_exitButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void Navigation_page::on_stat_Button_clicked()
{
    int num1, num2;
    if(Statistics(userLog, num1, num2)){
        QString myStr = "Общая кол-во решенных задач: " + QString::number(num1 + num2) +
                        "\n=========================\nКол-во правильных ответов: " + QString::number(num1) +
                        "\n=========================\nКол-во неправильных ответов: " + QString::number(num2);
        ui->label_2->setText(myStr);
        ui->stackedWidget->setCurrentIndex(1);
    }
}


void Navigation_page::on_exit_Button_clicked()
{
    close();
}


void Navigation_page::on_submit_task1_button_clicked()
{

    QString answer = ui->answer_task1->text();
    //qDebug()<< decryptMessage(graph);

    if(Submit_task1("graph&" + answer + "&" + decryptMessage(graph))){
        ui->stackedWidget->setCurrentIndex(0);
    }
    else {
        ui->answer_task1->clear();
        QMessageBox::warning(this, "Ошибка", "Неправильный ответ");
    }
    ui->answer_task1->clear();
}


void Navigation_page::on_submit_task2_Button_clicked()
{
    QString answer = ui->answer_2->text();

    if(Submit_task1(answer)){
        ui->stackedWidget->setCurrentIndex(0);
    }
    else {
        ui->answer_2->clear();
        QMessageBox::warning(this, "Ошибка", "Неправильный ответ");
    }
}

