#include "apiCalls.h"
#include <QJsonDocument>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QDebug>


OmpApiCalls::OmpApiCalls( QObject* parent )
    : QObject( parent )
{ }

QJsonObject OmpApiCalls::callSync( const QString& url, const QJsonObject& params )
{
    qDebug() << "OmpApiCalls::call" << url;
    qDebug() << params;

    QString inputArgs = QJsonDocument( params ).toJson();
    QByteArray  inputArgsUtf8 = inputArgs.toUtf8();

    QNetworkAccessManager networkMng;

    QUrl _url = url;
    QNetworkRequest request( _url );

    request.setHeader( QNetworkRequest::ContentTypeHeader, "application/json" );
    request.setHeader( QNetworkRequest::ContentLengthHeader, inputArgsUtf8.size() );

    QNetworkReply* reply = networkMng.post( request, inputArgsUtf8 );

    QEventLoop loop;
    QObject::connect( reply, SIGNAL(finished()), &loop, SLOT(quit()) );

    loop.exec();

    QJsonObject res;

    if( reply->error() != QNetworkReply::NoError )
    {
        QJsonObject jsonErrorObj;
        jsonErrorObj.insert( "Code", QJsonValue( reply->error() ) );
        jsonErrorObj.insert( "Category", QJsonValue( QString( "rest::ErrorCategory::Network" ) ) );
        jsonErrorObj.insert( "String", QJsonValue( reply->errorString() ) );
        jsonErrorObj.insert( "Value", QJsonValue( QJsonValue::Undefined ) );

        res.insert( "error", jsonErrorObj );

        qDebug() << "res" << res;

        return res;
    }

    QJsonParseError error;
    res = QJsonDocument::fromJson( reply->readAll(), &error ).object();

    if( QJsonParseError::NoError != error.error )
    {
        // fill parse error here
        return QJsonObject();
    }

    qDebug() << "res" << res;

    return res;
}

bool OmpApiCalls::isSucceded( const QJsonObject& apiCallResult, QString& errStr )
{
    if( apiCallResult.isEmpty() )
        return false;

    if( !apiCallResult[ "error" ].isObject() )
        return true;

    QJsonObject err = apiCallResult[ "error" ].toObject();
    if( err[ "Code" ] != QJsonValue( 0 ) )
    {
        errStr = err[ "String" ].isString() ? err[ "String" ].toString() : "Undefined error";
        return false;
    }

    return true;
}
