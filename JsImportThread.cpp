#include "JsImportThread.h"
#include <QJSEngine>
#include <QJSValue>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include "apiCalls.h"
#include "jsUtils.h"

JsImportThread::JsImportThread( QProgressBar* progressBar, const QString& file, const QString& function, QObject *parent )
    : QThread( parent )
{
    jsFile = file;
    jsFunction = function;
    importProgressBar = progressBar;
}

void JsImportThread::run()
{
    QJSEngine engine;

    {
        QString contents;

        QFile scriptFile( jsFile );
        if( !scriptFile.open( QIODevice::ReadOnly ) )
        {
            emit appendLog( QString( "Fail to open file \'%1\'" ).arg( jsFile ) );
            return;
        }

        QTextStream stream( &scriptFile );
        contents = stream.readAll();

        scriptFile.close();

        QJSValue ret = engine.evaluate( contents, jsFile );
        if( ret.isError() )
        {
            emit appendLog( QString( "Uncaught exception: %1" ).arg( ret.toString() ) );
            return;
        }
    }

    QStringList imports;

    QJSValue includesJsArray = engine.globalObject().property( "includes" );
    if( includesJsArray.isObject() )
    {
        Q_ASSERT( includesJsArray.isArray() );

        QString path = jsFile.left( jsFile.lastIndexOf( '/' ) );

        int length = includesJsArray.property( "length" ).toInt();
        for( long j = 0; j < length; j++ )
        {
            QJSValue import = includesJsArray.property( j );
            imports << path + "/" + import.toString();
        }
    }

    foreach( QString importPath, imports )
    {
        QString contents;

        QFile scriptFile( importPath );
        if( !scriptFile.open( QIODevice::ReadOnly ) )
        {
            emit appendLog( QString( "Fail to open file \'%1\'" ).arg( importPath ) );
            return;
        }

        QTextStream stream( &scriptFile );
        contents = stream.readAll();

        scriptFile.close();

        QJSValue ret = engine.evaluate( contents, importPath );
        if( ret.isError() )
        {
            emit appendLog( QString( "Uncaught exception while evaluate file \'%1\': %2" ).arg( importPath ).arg( ret.toString() ) );
            return;
        }
    }

    OmpApiCalls* ompApi = new OmpApiCalls();
    QJSValue ompApiValue = engine.newQObject( ompApi );

    engine.globalObject().setProperty( "API", ompApiValue );

    OmpApiJsUtils* jsUtils = new OmpApiJsUtils();
    QJSValue jsUtilsValue = engine.newQObject( jsUtils );

    QObject::connect( jsUtils, SIGNAL( log(const QString&) ), this, SIGNAL( appendLog(const QString&) ) );

    engine.globalObject().setProperty( "utils", jsUtilsValue );

    QJSValue runImportFunction = engine.globalObject().property( jsFunction );

    QJSValue res = runImportFunction.call( QJSValueList() );

    if( res.isError() )
    {
        emit appendLog( QString( "Uncaught exception: %1" ).arg( res.toString() ) );
        return;
    }

    emit appendLog( res.toString() );
}

//void JsImportThread::appendLog( const QString& msg )
//{
//}
