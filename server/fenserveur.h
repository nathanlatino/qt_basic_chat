#pragma once
#include <QtWidgets>
#include <QtNetwork>
#include <QDebug>

#include "ui_fenserveur.h"


class FenServeur : public QWidget, private Ui::FenServeur
{
    Q_OBJECT
public:
    FenServeur(QWidget *parent = 0);
    void sendAll(const QString &message);
private slots:
    void connectionCustomer();
    void receiveData();
    void disconnectCustomer();

private:
    void connectSloSig();
    void state();
    QString readData(QTcpSocket *socket);
    QTcpServer* server;
    QList<QTcpSocket *> customers;
};
