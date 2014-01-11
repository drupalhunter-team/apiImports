#include "jsUtils.h"
#include <QFileDialog>
#include <QDebug>
#include <QTextStream>
#include <QThread>

#include "JsImportThread.h"

OmpApiJsUtils::OmpApiJsUtils( QObject* parent )
    : QObject( parent )
{ }

QJSValue OmpApiJsUtils::chooseFile()
{
//    QFileDialog fd = new QFileDialog( this );
//    fd.moveToThread( );

//    JsImportThread* currentThread = qobject_cast<JsImportThread*>( QThread::currentThread() );
//    QThread* guiThread = currentThread->getGuiThread();

//    QFileDialog* fd = new QFileDialog( nullptr );
//    fd->moveToThread( guiThread );

//    fd->show();

//    long sdf = 789;

    QString filePath = QFileDialog::getOpenFileName( nullptr, tr("Choose file") );
    return filePath;

//    return "";
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
