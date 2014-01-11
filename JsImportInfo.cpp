#include "JsImportInfo.h"
#include <QJSValue>

JsImportInfo::JsImportInfo( QObject* parent )
    : QObject( parent )
{ }

JsImportInfo::JsImportInfo( const JsImportInfo* src, QObject* parent )
    : QObject( parent )
{
    File = src->File;
    Name = src->Name;
    PrepareFunction = src->PrepareFunction;
    ImportFunction = src->ImportFunction;
}

JsImportInfo::JsImportInfo( const QString& importFile, const QJSValue& jsValue, QObject* parent )
    : QObject( parent )
{
    if( jsValue.isUndefined() )
        return;

    Q_ASSERT( jsValue.isObject() );

    File = importFile;
    Name = jsValue.property( "importName" ).toString();
    PrepareFunction = jsValue.property( "prepareFunction" ).toString();
    ImportFunction = jsValue.property( "importFunction" ).toString();
}
