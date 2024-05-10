#ifndef DATABASE_H
#define DATABASE_H
#include <QCoreApplication>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QVariant>
#include <QStringList>

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
    const QMap<QString,QString> queryMap = {
        {"auth", "SELECT * FROM users WHERE Login = :param_1 AND pass = :param_2"},
        {"reg", "INSERT INTO users (Login, pass, mail) VALUES (:param_1, :param_2, :param_3)"},
        {"checkUser", "SELECT * FROM users WHERE Login = :log"}
    };
protected:
    dataBase();
    dataBase(const dataBase&)=delete;
    dataBase& operator = (dataBase &)=delete;
    friend class dataBaseDestroyer;
public:
    ~dataBase();
    static dataBase* getInstance();
    QStringList send_query(QStringList queryStr);
   // void connect();
    //void disconnect();
};

#endif // DATABASE_H
