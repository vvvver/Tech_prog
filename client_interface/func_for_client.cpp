#include "func_for_client.h"
#include "singletonclient.h"
#include "SHA512.h"
//#include <iostream>
//#include <sstream>


bool auth(QString login, QString password)
{
    //password = MyHash(password);
    SHA512 sha512;
    std::string pass = password.toStdString();
    QString pass_hash = QString::fromStdString(sha512.hash(pass));

    QString res =SingletonClient::getInstance()
                      ->seng_msg_to_server("auth&"+login + "&" + pass_hash);
    return "auth-"!=res;
}

bool reg(QString login, QString password, QString mail)
{
    SHA512 sha512;
    std::string pass = password.toStdString();
    QString pass_hash = QString::fromStdString(sha512.hash(pass));

    QString result_reg = SingletonClient::getInstance()
                             ->seng_msg_to_server("reg&"+login + "&" + pass_hash +"&" + mail);
    return "reg-"!= result_reg;
}

bool Submit_task1(QString taskNum, QString variant, QString answer)
{
    QString result_task = SingletonClient::getInstance()
                             ->seng_msg_to_server("check&"+taskNum + "&" + variant +"&" + answer);
    return "check-" != result_task;
}

bool Statistics(QString any, int& num1, int& num2)
{
    QString result_stat = SingletonClient::getInstance()
                              ->seng_msg_to_server("stat&"+any);

    return init_Int_Var(result_stat, num1, num2);
}

bool is_Pos_Int(QString str) {
    bool ok;
    int num = str.toInt(&ok);
    return ok && num > 0;
}

bool init_Int_Var(QString input, int& num1, int& num2) {
    QStringList parts = input.split('&');
    if (parts.size() != 3) {
        return false;
    }

    if (!is_Pos_Int(parts[1])) {
        return false;
    } else {
        num1 = parts[1].toInt();
    }

    if (!is_Pos_Int(parts[2])) {
        return false;
    } else {
        num2 = parts[2].toInt();
    }

    return true;
}

QString Random_Graph(int num){
    QFile file("C:/Users/abdua/Desktop/client_interface/graph_query.txt");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug()<< "Не удалось открыть файл";
    }
    QTextStream in(&file);

    for(int i = 1; i < num; i++){
        in.readLine();
    }

    QString line = in.readLine();
    qDebug()<< line;
    file.close();

    return line;
}








