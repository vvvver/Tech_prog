#include "func_for_client.h"
#include "singletonclient.h"
//#include <iostream>
//#include <sstream>

QString MyHash(QString str)
{
    QByteArray byteArray = str.toUtf8();
    QByteArray hash = QCryptographicHash::hash(byteArray, QCryptographicHash::Sha3_512);
    return str = hash.toBase64();
}

bool auth(QString login, QString password)
{
    password = MyHash(password);
    QString res =SingletonClient::getInstance()
                      ->seng_msg_to_server("auth&"+login + "&" + password);
    return "auth-"!=res;
}

bool reg(QString login, QString password, QString mail)
{
    password = MyHash(password);

    QString result_reg = SingletonClient::getInstance()
                             ->seng_msg_to_server("reg&"+login + "&" + password +"&" + mail);
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








