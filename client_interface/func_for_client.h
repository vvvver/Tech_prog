#ifndef FUNC_FOR_CLIENT_H
#define FUNC_FOR_CLIENT_H


#include <QObject>
#include <QQmlEngine>

#include <QCryptographicHash>
#include <QByteArray>
#include <QString>
#include <QDebug>
#include <QFile>
#include <QTextStream>

bool auth(QString,QString);

bool reg(QString, QString, QString);

bool Submit_task1(QString);

bool Submit_task2(QString, QString, QString);

bool Statistics(QString, int& num1, int& num2);

bool is_Pos_Int(QString);

bool init_Int_Var(QString, int& num1, int& num2);

QString Random_Graph(int num);


#endif // FUNC_FOR_CLIENT_H
