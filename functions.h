#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <QString>

    QByteArray parsing (QString data_from_client);
    QByteArray auth (QString log, QString pass);
    QByteArray reg (QString log, QString pass, QString mail);
    QByteArray graph (QStringList array);


#endif // FUNCTIONS_H
