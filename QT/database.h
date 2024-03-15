#ifndef DATABASE_H
#define DATABASE_H
#include <QCoreApplication>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QVariant>

class dataBase;

class dataBaseDestroyer
{
private:
    dataBase * p_instance;
public:
    ~dataBaseDestroyer();
    void initialize(dataBase * p){p_instance = p;};
};

class dataBase {
private:
    static dataBase * p_instance;
    static dataBaseDestroyer destroyer;
    QSqlDatabase mydb;
protected:
    dataBase() {}
    dataBase(const dataBase&);
    dataBase& operator = (dataBase &);
    friend class dataBaseDestroyer;
public:
    ~dataBase();
    static dataBase* getInstance();
    QSqlQuery send_query(QString queryStr);
    void connect();
    void disconnect();
};

#endif // DATABASE_H
