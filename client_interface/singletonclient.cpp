#include "singletonclient.h"

SingletonClient::SingletonClient(QObject *parent) : QObject(parent)
{
    mTcpSocket = new QTcpSocket(this);
    mTcpSocket->connectToHost("127.0.0.1", 33333);

    connect(mTcpSocket, SIGNAL(readyRead()),
            this, SLOT(slotServerRead()));
}

SingletonClient* SingletonClient::getInstance() {
    if (!p_instance){
        p_instance = new SingletonClient();
        destroyer.initialize(p_instance);
    }
    return p_instance;
}

QString SingletonClient::seng_msg_to_server(QString query) {
    mTcpSocket->write(query.toUtf8());
//}
    mTcpSocket->waitForReadyRead();
//void SingletonClient::slotServerRead(){
    QString msg = "";
    while (mTcpSocket->bytesAvailable()>0) {
        QByteArray array = mTcpSocket->readAll();
        msg.append(array);
    }
    qDebug() << msg;
    //emit message_from_server(msg);
    return msg;
}

SingletonClient::~SingletonClient()
{
    mTcpSocket->close();
}

SingletonClient* SingletonClient::p_instance;
SingletonDestroyer SingletonClient::destroyer;
