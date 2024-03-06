#include "func_for_client.h"
#include <QCryptographicHash>
#include <QByteArray>
#include <QString>
#include <QDebug>
#include <string>

void MyHash(QString str)
{
    std::string newstr = str.toStdString();
    const char* char_array = newstr.c_str();
    QByteArray byteArray;
    byteArray.append(char_array);
    QByteArray hash = QCryptographicHash::hash(byteArray, QCryptographicHash::Sha3_512);
    str = hash.toBase64();
}
