#ifndef APICALLS_H
#define APICALLS_H

#include <QObject>
#include <QJsonObject>

class OmpApiCalls : public QObject
{
    Q_OBJECT

public:
    OmpApiCalls( QObject* parent = nullptr );

    Q_INVOKABLE QJsonObject callSync( const QString& url, const QJsonObject& params );

    Q_INVOKABLE bool isSucceded( const QJsonObject& apiCallResult, QString& errStr = QString() );
};

#endif // APICALLS_H
