#include "jsUtils.h"
#include <QFileDialog>
#include <QDebug>
#include <QTextStream>

OmpApiJsUtils::OmpApiJsUtils( QObject* parent )
    : QObject( parent )
{ }

QJSValue OmpApiJsUtils::chooseFile()
{
    QString filePath = QFileDialog::getOpenFileName( nullptr, tr("Choose file") );
    return filePath;
}

QJSValue OmpApiJsUtils::readFile( const QString& path )
{
    QFile file( path );
    if( !file.open( QIODevice::ReadOnly ) )
    {
        qDebug() << "Fail to open file \"" << path << "\"";
        return QJSValue();
    }

    QTextStream stream( &file );

    return QJSValue( stream.readAll() );
}

//QJSValue OmpApiJsUtils::log( const QString& msg )
//{
//    qDebug() << msg;
//    return QJSValue();
//}
