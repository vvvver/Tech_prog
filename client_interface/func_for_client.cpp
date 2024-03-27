#include "func_for_client.h"
#include "singletonclient.h"
//#include "mainwindow.h"
#include <QDebug>
#include <string>

void MyHash(QString str)
{
    std::string newstr = str.toStdString();
    const char* char_array = newstr.c_str();
    QByteArray byteArray;
    byteArray.append(char_array);
    QByteArray hash = QCryptographicHash::hash(byteArray, QCryptographicHash::Sha3_512);
    str = hash.toBase64();
}

bool auth(QString login,QString password)
{
    MyHash(password);
    QString res =SingletonClient::getInstance()->seng_msg_to_server("auth&"+login + "&" + password);

    return "auth-"!=res;
}

bool reg(QString login, QString password, QString mail){
    MyHash(password);

    QString result_reg = SingletonClient::getInstance()
                             ->seng_msg_to_server("reg&"+login + "&" + password +"&" + mail);
    return "reg-"!= result_reg;
}

bool Submit_task1(QString taskNum, QString variant, QString answer){
    QString result_task = SingletonClient::getInstance()
                             ->seng_msg_to_server("check&"+taskNum + "&" + variant +"&" + answer);
    return "check-" != result_task;
}

bool Statistics(){
    //QString ex = getLog();
    QString correct_answer = "stat&3&6&-7";
    QString result_stat = SingletonClient::getInstance()
                              ->seng_msg_to_server("stat&");
    //qDebug() << ex;
    return correct_answer == result_stat;
}


/*void LoginInfo::setLog(QString any){
    ex->UserLog = any;
}

QString LoginInfo::getLog(){
    return ex->UserLog;
}*/







