#ifndef JSIMPORTINFO_H
#define JSIMPORTINFO_H

#include <QObject>
//#include <QString>

class QJSValue;

class JsImportInfo : public QObject
{
     Q_OBJECT

public:
    JsImportInfo( QObject* parent = nullptr );
    JsImportInfo( const QJSValue& jsValue, QObject* parent = nullptr );

public:
    QString Name;
    QString Function;
    QString File;
};

#endif // JSIMPORTINFO_H
