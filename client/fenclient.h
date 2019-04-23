#pragma once

#include <QtWidgets>
#include <QtNetwork>
#include "ui_fenclient.h"
#include <QDebug>

class QTcpSocket;
class FenClient : public QWidget, Ui::FenClient
{
    Q_OBJECT
public:
    FenClient(QWidget *parent = 0);

private slots:

    void on_btnConnect_clicked();
    void on_btnSend_clicked();
    void on_ledMessage_returnPressed();
    void receiveData();
    void connectChat();
    void disconnectChat();
    void errorSocket(QAbstractSocket::SocketError);

private:
    QString readData();
    void connectSloSig();
    QTcpSocket *socket;
};
