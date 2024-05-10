#include "database.h"


dataBase* dataBase::p_instance = nullptr;
dataBaseDestroyer dataBase::destroyer;

dataBaseDestroyer::~dataBaseDestroyer() {
    delete p_instance;
}


dataBase::~dataBase() {
    if (p_instance) {
        mydb.close();
        delete p_instance;
    }
}

dataBase* dataBase::getInstance() {
    if (!p_instance)
    {
        p_instance = new dataBase();
        destroyer.initialize(p_instance);
    }
    return p_instance;
}

dataBase::dataBase() {
    mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("../QT/sqlite.db");

    if(!mydb.open())
        qDebug()<<mydb.lastError().text();
}


QStringList dataBase::send_query(QStringList queryStrList) {
    QSqlQuery myquery(mydb);
    QString queryStr = queryMap[queryStrList[0]];
    myquery.prepare(queryStr);
    for(int i = 1; i < queryStrList.size(); ++i){
        myquery.bindValue(":param_" + QString::number(i), queryStrList[i]);
    }
    bool success = myquery.exec();
    QStringList res;

    if (queryStrList[0] == "checkUser") {
        myquery.prepare(queryMap[queryStrList[0]]);
        myquery.bindValue(":log", queryStrList[1]);
        if (myquery.exec() && myquery.next()) {
            QString login = myquery.value("Login").toString();
            res << login;
        }
    } else if(queryStrList[0] == "auth") {
        if(myquery.next()) {
            QString login = myquery.value("Login").toString();
            QString pass = myquery.value("pass").toString();
            QString mail = myquery.value("mail").toString();
            QString id = myquery.value("ID").toString();
            QString userInfo = QString("ID: %1, Login: %2, pass: %3, mail: %4").arg(id, login, pass, mail);
            res << userInfo;
        }
    } else if(queryStrList[0] == "reg") {
        if(success && myquery.numRowsAffected() > 0) {
            QSqlQuery idQuery(mydb);
            idQuery.exec("SELECT last_insert_rowid()");
            int userId = 0;
            if (idQuery.next()) {
                userId = idQuery.value(0).toInt();
            }
            QSqlQuery userQuery(mydb);
            userQuery.prepare("SELECT Login, mail, pass, ID FROM users WHERE ID = :id");
            userQuery.bindValue(":id", userId);
            if (userQuery.exec() && userQuery.next()) {
                QString login = userQuery.value("Login").toString();
                QString pass = userQuery.value("pass").toString();
                QString mail = userQuery.value("mail").toString();
                QString id = userQuery.value("ID").toString();
                QString userInfo = QString("ID: %1, Login: %2, pass: %3, mail: %4").arg(id, login, pass, mail);
                res << userInfo;
            }
        } else {
            qDebug() << "строки не затронуты";
        }
    }
    return res;
}


    /*
    if(queryStrList[0] == "auth") {
        if(myquery.next()) {
            QString userLog = myquery.value("log").toString();
            res << "auth_success" << userLog;
        } else {
            res << "auth_fail";
        }
    } else if (queryStrList[0] == "reg") {
        if(myquery.numRowsAffected() > 0) {
            res << "reg_success";
        } else {
            res << "reg_fail";
        }
    }*/
