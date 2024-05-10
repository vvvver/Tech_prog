#include "functions.h"
#include <QString>
#include <QDebug>
#include <QCoreApplication>
#include <QStringList>
#include "database.h"
#include "graph.h"

QByteArray parsing (QString data_from_client) {
    QStringList data_from_client_list = data_from_client.split(QLatin1Char('&'));
    if ((data_from_client_list[0] == "auth" and data_from_client_list.size() < 4) or (data_from_client_list[0] == "reg" and data_from_client_list.size() < 5)) {
        return "error\r\n";
    }
    QString nameOfFunc = data_from_client_list.front();
    data_from_client_list.pop_front();
    if (nameOfFunc == "auth")
        return auth(data_from_client_list.at(0), data_from_client_list.at(1));
    if (nameOfFunc == "reg")
        return reg(data_from_client_list.at(0), data_from_client_list.at(1), data_from_client_list.at(2));
    if(nameOfFunc == "graph")
        return graph(data_from_client_list);
    else
        return "error1\r\n";
}

QByteArray auth (QString log, QString pass) {
    QStringList response = dataBase::getInstance()->send_query(QStringList{"auth", log, pass});
    qDebug()<<response;
    if(!response.isEmpty()) {
        return QString("auth+ ").append(response[0] + "\r\n").toUtf8();
    } else {
        return QString("auth-\r\n").toUtf8();
    }
}

QByteArray reg (QString log, QString pass, QString mail) {
    QStringList checkUserExists = dataBase::getInstance()->send_query(QStringList{"checkUser", log});
    if(!checkUserExists.isEmpty()) {
        return QString("error: user already exists\r\n").toUtf8();
    }
    QStringList response = dataBase::getInstance()->send_query(QStringList{"reg", log, pass, mail});
    if(!response.isEmpty()) {
         return QString("reg+ ").append(response[0] + "\r\n").toUtf8();
    } else {
        return QString("reg- Registration failed\r\n").toUtf8();
    }
}

QByteArray graph(QStringList array) {
    if(array[0].length() > 1 or array[1].length() > 1) {
        return QString("invalid input\r\n").toUtf8();
    }
    list_graph new_graph;
    for(int i = 2; i < array.length(); i++) {
        new_graph.push(array[i].split(QLatin1Char('*'))[0].toInt(), array[i].split(QLatin1Char('*'))[1].toInt());
    }
    return QString(new_graph.BFS(array[0].toInt(), array[1].toInt()) + "\r\n").toUtf8();
}
//graph&1&4&0*1&0*2&1*0&1*3&2*0&2*3&2*4&3*1&3*2&4*2
//graph&0&7&0*1&0*2&1*0&1*3&1*4&2*0&2*5&2*6&3*1&3*4&4*1&4*3&4*6&5*2&5*6&6*2&6*4&6*5&6*7&7*6
//["2", "3", "2*3", "2*4", "3*5", ...]
