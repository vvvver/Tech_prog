#ifndef FUNC_FOR_CLIENT_H
#define FUNC_FOR_CLIENT_H


#include <QObject>
#include <QQmlEngine>

#include <QCryptographicHash>
#include <QByteArray>
#include <QString>
#include <QDebug>

void MyHash(QString str);

bool auth(QString,QString);

bool reg(QString, QString, QString);

bool Submit_task1(QString, QString, QString);

bool Statistics();


/*class LoginInfo {
public:
    LoginInfo* ex;
    void  setLog(QString);
    QString getLog();
private:
    QString UserLog;
};*/

//LoginInfo* ex;

#endif // FUNC_FOR_CLIENT_H
