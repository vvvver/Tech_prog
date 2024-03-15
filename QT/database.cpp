#include "database.h"

dataBase* dataBase::p_instance = nullptr;
dataBaseDestroyer dataBase::destroyer;

dataBaseDestroyer::~dataBaseDestroyer() {
    delete p_instance;
}


dataBase::~dataBase() {
    if (mydb.isOpen())
        disconnect();
    if (p_instance)
        delete p_instance;
}

dataBase* dataBase::getInstance() {
    if (!p_instance)
    {
        p_instance = new dataBase();
        destroyer.initialize(p_instance);
    }
    return p_instance;
}

void dataBase::connect() {
    QSqlDatabase mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("Test.db");

    if(!mydb.open())
        qDebug()<<mydb.lastError().text();
}
void dataBase::disconnect() {
    mydb.close();
}

QSqlQuery dataBase::send_query(QString queryStr) {
    QSqlQuery myquery;
    if(myquery.prepare(queryStr)) {
    myquery.exec();
    }
    return myquery;
}
