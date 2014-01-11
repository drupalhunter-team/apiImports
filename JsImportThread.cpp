#include "JsImportThread.h"
#include <QJSEngine>
#include <QJSValue>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include "apiCalls.h"
#include "jsUtils.h"
#include "JsImportDialog.h"
#include "JsImportInfo.h"
#include "JsImportEngine.h"

JsImportThread::JsImportThread( const JsImportInfo* info, QObject *parent )
    : QThread( parent )
{
    _jsImportInfo = info;
}

//JsImportThread::JsImportThread( QThread* guiThread, JsImportDialog* importDlg, const JsImportInfo* importInfo, QObject *parent )
//    : QThread( parent )
//{
//    _guiThread = guiThread;
//    _jsImportInfo = new JsImportInfo( importInfo, this );
//    jsImportDlg = importDlg;
//}

void JsImportThread::setImportPrepareResults( const QJsonObject& prepareResults )
{
    _prepareResults = prepareResults;
}

void JsImportThread::setImportDialogProgressWidget( const JsImportDialog* importDlg )
{
    _importProgressWidget = importDlg;
}

QThread* JsImportThread::getGuiThread()
{
    return _guiThread;
}

void JsImportThread::run()
{
    JsImportEngine __engine;

    QObject::connect( &__engine, SIGNAL( appendLog(const QString&) ), this, SIGNAL( appendLog(const QString&) ) );

    if( !__engine.init( _jsImportInfo ) )
        return;

    __engine.setImportProgressWidget( _importProgressWidget );

    if( !__engine.hasImportFunction() )
        return;

    __engine.runImportFunction( _prepareResults );

    return;
/*
    QJSEngine engine;

    {
        QString contents;

        QFile scriptFile( _jsImportInfo->File );
        if( !scriptFile.open( QIODevice::ReadOnly ) )
        {
            emit appendLog( QString( "Fail to open file \'%1\'" ).arg( _jsImportInfo->File ) );
            return;
        }

        QTextStream stream( &scriptFile );
        contents = stream.readAll();

        scriptFile.close();

        QJSValue ret = engine.evaluate( contents, _jsImportInfo->File );
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

        QString path = _jsImportInfo->File.left( _jsImportInfo->File.lastIndexOf( '/' ) );

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

    JsImportProgress* progress = new JsImportProgress( jsImportDlg );
    QJSValue progressJsValue = engine.newQObject( progress );

    engine.globalObject().setProperty( "progress", progressJsValue );

    QJSValue prepareFunction = engine.globalObject().property( _jsImportInfo->PrepareFunction );

    QJSValue runImportFunction = engine.globalObject().property( _jsImportInfo->ImportFunction );

    QJSValue res = runImportFunction.call( QJSValueList() );

    if( res.isError() )
    {
        emit appendLog( QString( "Uncaught exception: %1" ).arg( res.toString() ) );
        return;
    }

    emit appendLog( res.toString() );*/
}

//void JsImportThread::appendLog( const QString& msg )
//{
//}
