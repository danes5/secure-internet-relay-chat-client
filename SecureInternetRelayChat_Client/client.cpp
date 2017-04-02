#include "client.h"

Client::Client(QObject *parent) : QObject(parent), port(4500), serverName("server not yet set up")
{
    activeClients.append("Johny");
    activeClients.append("Billy");
}

const QList<QString> *Client::getActiveClients()
{
    return &activeClients;

}

void Client::sendCreateChannelRequest(QString name)
{
    qDebug() << "sending create channel request to the server\n";
}

void Client::receiveCreateChannelRequest(QString name)
{

}

void Client::processReadyRead()
{
    // every communication over network is in form:
    //  1. ID  --REQUIRED
    //  2. Type of message  --REQUIRED
    //  3. Length of the Body of message
    //  4. Body of the message of length Length

    buffer = serverConnection->readAll();
    switch (receivingAction) {
    case NOTHING:
        id = buffer.toULongLong();
        buffer.clear();
        verifyServerMessageID();
        receivingAction = RECEIVED_ID;
        break;

    case RECEIVED_ID:
        currentReceivingType = QString::fromUtf8(buffer);
        buffer.clear();
        processReceivingType();
        break;


    case RECEIVED_TYPE:
        expectedDataSize = buffer.toULongLong();
        buffer.clear();
        receivingAction = RECEIVED_LENGTH;
        break;

    case RECEIVED_LENGTH:
        if (buffer.length() == expectedDataSize)
            processReceivingType();
        break;

    }

}

void Client::sendMessage(QString dest, QString text)
{
    foreach (Channel* channel, activeChannels) {
        if (channel->getOtherClientName() == dest){
            channel->sendMessage(text);
            return;
        }
    }
    // open channel for client not found, which means inconsistenct between our UI and client class.
    qWarning() << "client not found\n";
}

void Client::registerToServer(QString name)
{
    serverConnection = new QSslSocket(this);
    serverConnection->connectToHostEncrypted(serverName, port);
    currentReceivingType = REGISTER_REPLY;
}

QList<QString> Client::getActiveNamesFromServer()
{

}

void Client::acceptCreateChannelRequest(QString name)
{

}

void Client::registrationSuccessful()
{
       emit onRegistrationSuccessful();
    isRegistered = true;
}

void Client::registrationFailed()
{

}

void Client::verifyServerMessageID()
{

}

void Client::processReceivingType()
{
    // this is just confirmation of a registration accepted by the server
    // no more data is expected
    if (currentReceivingType == "ACC_REG"){
        receivingAction = NOTHING;
        registrationSuccessful();
        return;
    }

    if (currentReceivingType == "DEC_REG"){
        receivingAction = NOTHING;
        registrationFailed();
        return;
    }

    // this means we are to process Get list of active clients from the server
    if (currentReceivingType == "GET_CLI"){
        // if state is in received_id then it means we either continue to reading the
        //rest of the message or we have finished reading it whole
        if (receivingAction == RECEIVED_ID ){
            receivingAction = RECEIVED_TYPE;
        }else{
            // now receivingAction must be Received Length and whole message is read by now
            receivingAction = NOTHING;
            QString receivedCLientsList;
            //receivedCLientsList << buffer;
            // now we have to parse string into list of clients

        }
        return;
    }

    if (currentReceivingType == "ACC_REQ"){
        if (receivingAction == RECEIVED_ID ){
            receivingAction = RECEIVED_TYPE;
        }else{
            // now receivingAction must be Received Length and whole message is read by now
            receivingAction = NOTHING;
            QJsonObject receivedCLientsList;
            //receivedCLientsList = buffer.to;
            // now we have to parse string into list of clients
        }
    return;
    }

    if (currentReceivingType == "DEC_REQ"){
        receivingAction = NOTHING;
        registrationFailed();
    }
}

void Client::updateActiveClients(){

}
