#include "jsUtils.h"
#include <QFileDialog>
#include <QDebug>
#include <QTextStream>
#include <QThread>

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

void OmpApiJsUtils::sleep( int usec )
{
    QThread::usleep( usec );
}
