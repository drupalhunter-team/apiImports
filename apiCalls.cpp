#include "apiCalls.h"
#include <QDebug>

OmpApiCalls::OmpApiCalls( QObject* parent )
    : QObject( parent )
{ }

QJsonValue OmpApiCalls::call( const QString& url, QJsonValue params )
{
    qDebug() << "OmpApiCalls::call" << url;
    qDebug() << params;

    QJsonValue res;
    return res;
}
