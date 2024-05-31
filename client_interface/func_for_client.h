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

// \brief авторизация
bool auth(QString,QString);

// \brief регистрация
bool reg(QString, QString, QString);

// \brief задача 1
bool Submit_task1(QString);

// \brief задача 2
bool Submit_task2(QString, QString, QString);

// \brief статистика
bool Statistics(QString, int& num1, int& num2);

// \brief проверка на число
bool is_Pos_Int(QString);

// \brief инициализация перемнной integer
bool init_Int_Var(QString, int& num1, int& num2);

// \brief создание графа
QString Random_Graph(int num);


#endif // FUNC_FOR_CLIENT_H
