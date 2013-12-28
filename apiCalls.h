#ifndef APICALLS_H
#define APICALLS_H

#include <QObject>
#include <QJsonValue>

class OmpApiCalls : public QObject
{
    Q_OBJECT

public:
    OmpApiCalls( QObject* parent = nullptr );

    Q_INVOKABLE QJsonValue call( const QString& url, QJsonValue params );
};

#endif // APICALLS_H
