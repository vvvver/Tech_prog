#ifndef SINGLETONCLIENT_H
#define SINGLETONCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QtNetwork>
#include <QByteArray>
#include <QDebug>


class SingletonClient;

class SingletonDestroyer
{
private:
    SingletonClient* p_instance;
public:
    ~SingletonDestroyer() { delete p_instance;}
    // \brief инициализация клиента
    void initialize(SingletonClient* p){p_instance = p;};
};


class SingletonClient : public QObject
{
    Q_OBJECT

private:
    static SingletonClient* p_instance;
    static SingletonDestroyer destroyer;
    QTcpSocket * mTcpSocket;
protected:
    explicit SingletonClient (QObject *parent = nullptr);
    SingletonClient(SingletonClient&) = delete;
    SingletonClient& operator = (SingletonClient&) = delete;
    ~SingletonClient();
    friend class SingletonDestroyer;
public:
    static SingletonClient* getInstance();

    // \brief отправка сообщения на сервер
    QString seng_msg_to_server(QString query);
//signals:
//    void message_from_server(QString msg);
//private slots:
 //   void slotServerRead();
};

#endif // SINGLETONCLIENT_H

