#include "fenserveur.h"


FenServeur::FenServeur(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);
    server = new QTcpServer(this);
    server->listen(QHostAddress::Any, 50885);
    state();
    connectSloSig();
}

void FenServeur::connectSloSig() {
    connect(server, SIGNAL(newConnection()), this, SLOT(connectionCustomer()));
}

void FenServeur::state(){
    if(server->isListening()){
        lblState->setText("Le serveur a été démarré sur le port <b>50885</b>."
                          "<br/>Des clients peuvent maintenant se connecter.");
    } else {
        lblState->setText("Le serveur n'a pas pu être démarré. Raison :"
                          "\nL'adresse est déjà utilisée");
    }
}

void FenServeur::sendAll(const QString &message) {
    foreach (QTcpSocket* customer, customers) {
        customer->write(message.toUtf8());
     }
}

void FenServeur::connectionCustomer() {
    QTcpSocket *newCustomer = server->nextPendingConnection();
    QString msg = "<i>Un utilisateur s'est connecté</i>";
    connect(newCustomer, SIGNAL(readyRead()), this, SLOT(receiveData()));
    connect(newCustomer, SIGNAL(disconnected()), this, SLOT(disconnectCustomer()));
    sendAll(msg);
    customers.push_back(newCustomer);
}

void FenServeur::receiveData() {
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());;
    QString msg = readData(socket);
    sendAll(msg);
}

void FenServeur::disconnectCustomer() {
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    QString msg = "<i>Un utilisateur s'est déconnecté</i>";
    sendAll(msg);
    customers.removeAt(customers.indexOf(socket));
}

QString FenServeur::readData(QTcpSocket *socket)
{
    QDataStream in(socket);

    quint64 msgSize = socket->bytesAvailable();
    QByteArray buffer(msgSize, Qt::Uninitialized);
    in.readRawData(buffer.data(), msgSize);
    return QString(buffer);
}

