#include "mytcpserver.h"
#include <QDebug>
#include <QCoreApplication>
#include <QString>
#include "functions.h"
MyTcpServer::~MyTcpServer()
{

    mTcpServer->close();
    //server_status=0;
}

MyTcpServer::MyTcpServer(QObject *parent) : QObject(parent){
    mTcpServer = new QTcpServer(this);

    connect(mTcpServer, &QTcpServer::newConnection,
            this, &MyTcpServer::slotNewConnection);

    if(!mTcpServer->listen(QHostAddress::Any, 33333)){
        qDebug() << "server is not started";
    } else {
        //server_status=1;
        qDebug() << "server is started";
    }
}

void MyTcpServer::slotNewConnection() {
    while (mTcpServer->hasPendingConnections()) {
        QTcpSocket *clientSocket = mTcpServer->nextPendingConnection();
        int descriptor = clientSocket->socketDescriptor();
        mClientSockets[descriptor] = clientSocket;
        connect(clientSocket, &QTcpSocket::readyRead, this, &MyTcpServer::slotServerRead);
        connect(clientSocket, &QTcpSocket::disconnected, this, &MyTcpServer::slotClientDisconnected);
    }
}

void MyTcpServer::slotServerRead() {
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket*>(sender());
    if (!clientSocket) return;

    int descriptor = clientSocket->socketDescriptor();
    auto it = mClientSockets.find(descriptor);
    if (it == mClientSockets.end()) return; // Если сокет не найден в map, выходим из функции

    // Теперь используем найденный сокет для чтения данных
    clientSocket = it->second;
    QString res = "";
    while(clientSocket->bytesAvailable() > 0) {
        QByteArray array = clientSocket->readAll();
        qDebug() << array << "\n";
        if(array == "\x01") {
            clientSocket->write(res.toUtf8());
            res = "";
        } else {
            res.append(array);
        }
    }
    if (!res.isEmpty()) {
        qDebug() << res;
        clientSocket->write(parsing(res)); // Обработка и отправка ответа
    }
}
void MyTcpServer::slotClientDisconnected() {
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket*>(sender());
    int descriptor = clientSocket->socketDescriptor();
    mClientSockets.erase(descriptor);
    clientSocket->deleteLater();
}
