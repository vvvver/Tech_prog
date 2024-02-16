#ifndef FUNCIONS_SERVER_H
#define FUNCIONS_SERVER_H
#include <QString>


QByteArray parsing (QString data_from_client);
QByteArray auth (QString log, QString pass);
QByteArray reg (QString log, QString pass, QString mail);


#endif // FUNCIONS_SERVER_H
