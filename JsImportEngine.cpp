#include "JsImportEngine.h"
#include <QJSEngine>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QDebug>
#include <QJsonObject>
#include "JsImportInfo.h"
#include "apiCalls.h"
#include "jsUtils.h"
#include "JsImportDialog.h"


JsImportEngine::JsImportEngine( QObject* parent )
    : QObject( parent )
{
    _jsEngine = nullptr;
    _jsImportInfo = nullptr;
}

bool JsImportEngine::init( const JsImportInfo* info, QString& errStr )
{
    Q_ASSERT( info );

    if( _jsEngine )
        _jsEngine->deleteLater();

    if( _jsImportInfo )
        _jsImportInfo->deleteLater();

    _jsEngine = new QJSEngine( this );
    _jsImportInfo = new JsImportInfo( info, this );

    {
        QString contents;

        QFile scriptFile( _jsImportInfo->File );
        if( !scriptFile.open( QIODevice::ReadOnly ) )
        {
            errStr = QString( "Fail to open file \'%1\'" ).arg( _jsImportInfo->File );
            return false;
        }

        QTextStream stream( &scriptFile );
        contents = stream.readAll();

        scriptFile.close();

        QJSValue ret = _jsEngine->evaluate( contents, _jsImportInfo->File );
        if( ret.isError() )
        {
            errStr = QString( "Uncaught exception: %1" ).arg( ret.toString() );
            return false;
        }
    }

    QStringList imports;

    QJSValue includesJsArray = _jsEngine->globalObject().property( "includes" );
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
            errStr = QString( "Fail to open file \'%1\'" ).arg( importPath );
            return false;
        }

        QTextStream stream( &scriptFile );
        contents = stream.readAll();

        scriptFile.close();

        QJSValue ret = _jsEngine->evaluate( contents, importPath );
        if( ret.isError() )
        {
            errStr = QString( "Uncaught exception while evaluate file \'%1\': %2" ).arg( importPath ).arg( ret.toString() );
            return false;
        }
    }

    OmpApiCalls* ompApi = new OmpApiCalls( _jsEngine );
    QJSValue ompApiValue = _jsEngine->newQObject( ompApi );

    _jsEngine->globalObject().setProperty( "api", ompApiValue );

    OmpApiJsUtils* jsUtils = new OmpApiJsUtils( _jsEngine );
    QJSValue jsUtilsValue = _jsEngine->newQObject( jsUtils );

    QObject::connect( jsUtils, SIGNAL( log(const QString&) ), this, SIGNAL( appendLog(const QString&) ) );

    _jsEngine->globalObject().setProperty( "utils", jsUtilsValue );

//    JsImportProgress* progress = new JsImportProgress( jsImportDlg );
//    QJSValue progressJsValue = engine.newQObject( progress );
//
//    engine.globalObject().setProperty( "progress", progressJsValue );
//
//    QJSValue prepareFunction = engine.globalObject().property( _jsImportInfo->PrepareFunction );
//
//    QJSValue runImportFunction = engine.globalObject().property( _jsImportInfo->ImportFunction );
//
//    QJSValue res = runImportFunction.call( QJSValueList() );
//
//    if( res.isError() )
//    {
//        emit appendLog( QString( "Uncaught exception: %1" ).arg( res.toString() ) );
//        return;
//    }
//
//    emit appendLog( res.toString() );

    return true;
}

bool JsImportEngine::setImportProgressWidget( const JsImportDialog* dlg )
{
    Q_ASSERT( _jsImportInfo && _jsEngine );
    if( !_jsImportInfo || !_jsEngine )
        return false;

    JsImportProgress* progress = new JsImportProgress( dlg );
    QJSValue progressJsValue = _jsEngine->newQObject( progress );

    _jsEngine->globalObject().setProperty( "progress", progressJsValue );

    return true;
}

bool JsImportEngine::hasPrepareFunction()
{
    Q_ASSERT( _jsImportInfo && _jsEngine );
    if( !_jsImportInfo || !_jsEngine )
        return false;

    QJSValue prepareFunction = _jsEngine->globalObject().property( _jsImportInfo->PrepareFunction );
    if( prepareFunction.isCallable() )
        return true;

    return false;
}

bool JsImportEngine::runPrepareFunction( QJsonObject& prepareResults )
{
    Q_ASSERT( _jsImportInfo && _jsEngine );
    if( !_jsImportInfo || !_jsEngine )
        return false;

    QJSValue prepareFunction = _jsEngine->globalObject().property( _jsImportInfo->PrepareFunction );
    QJSValue res = prepareFunction.call( QJSValueList() );

    if( res.isError() )
    {
        emit appendLog( QString( "Uncaught exception: %1" ).arg( res.toString() ) );
        return false;
    }

    if( !res.isObject() )
    {
        return false;
    }

    prepareResults = _jsEngine->fromScriptValue<QJsonObject>( res );

    return true;
}

bool JsImportEngine::hasImportFunction()
{
    Q_ASSERT( _jsImportInfo && _jsEngine );
    if( !_jsImportInfo || !_jsEngine )
        return false;

    QJSValue importFunction = _jsEngine->globalObject().property( _jsImportInfo->ImportFunction );
    if( importFunction.isCallable() )
        return true;

    return false;
}

bool JsImportEngine::runImportFunction( const QJsonObject& prepareResults )
{
    Q_ASSERT( _jsImportInfo && _jsEngine );
    if( !_jsImportInfo || !_jsEngine )
        return false;


    QJSValue importFunction = _jsEngine->globalObject().property( _jsImportInfo->ImportFunction );
    QJSValue res = importFunction.call( QJSValueList() << _jsEngine->toScriptValue<QJsonObject>( prepareResults ) );

    if( res.isError() )
    {
        emit appendLog( QString( "Uncaught exception: %1" ).arg( res.toString() ) );
        return false;
    }

    return true;
}
