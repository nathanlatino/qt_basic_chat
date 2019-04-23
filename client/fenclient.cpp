#include "fenclient.h"


FenClient::FenClient(QWidget *parent) : QWidget(parent) {
    setupUi(this);
    socket = new QTcpSocket(this);
    connectSloSig();
}

void FenClient::connectSloSig() {
    connect(socket, SIGNAL(readyRead()), this, SLOT(receiveData()));
    connect(socket, SIGNAL(connected()), this, SLOT(connectChat()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnectChat()));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(errorSocket(QAbstractSocket::SocketError)));
}

void FenClient::on_btnConnect_clicked() {
    pteChat->appendHtml("<i>Tentative de connexion au chat...</i>");
    socket->connectToHost(ledIp->text(),sbxPort->value());
}

void FenClient::on_btnSend_clicked() {
    if(!ledMessage->text().isEmpty()){
        QString msg = ledPseudo->text()+ " : " + ledMessage->text();
        socket->write(msg.toUtf8());
        ledMessage->clear();
    }
}

void FenClient::on_ledMessage_returnPressed() {
    on_btnSend_clicked();
}

//https://stackoverflow.com/questions/12501140/qt-qstring-from-qdatastream
void FenClient::receiveData() {
    QString msg = readData();
    pteChat->appendHtml(msg);
}

void FenClient::connectChat() {
    pteChat->appendHtml("<i>Connexion réussie !</i>");
}

void FenClient::disconnectChat() {
    pteChat->appendHtml("<i>Déconnecté du chat...</i>");
}

void FenClient::errorSocket(QAbstractSocket::SocketError error) {
    pteChat->appendHtml("<i>Une erreur est survenue</i>");
}

QString FenClient::readData(){
    QDataStream in(socket);
    quint64 msgSize = socket->bytesAvailable();
    QByteArray buffer(msgSize, Qt::Uninitialized);
    in.readRawData(buffer.data(), msgSize);
    return QString(buffer);
}
