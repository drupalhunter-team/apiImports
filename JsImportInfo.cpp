#include "JsImportInfo.h"
#include <QJSValue>

JsImportInfo::JsImportInfo( QObject* parent )
    : QObject( parent )
{ }

JsImportInfo::JsImportInfo( const QJSValue& jsValue, QObject* parent )
    : QObject( parent )
{
    if( jsValue.isUndefined() )
        return;

    Q_ASSERT( jsValue.isObject() );

    Name = jsValue.property( "importName" ).toString();
    Function = jsValue.property( "importFunction" ).toString();
}

