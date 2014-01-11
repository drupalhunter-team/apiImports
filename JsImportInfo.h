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
    JsImportInfo( const JsImportInfo* src, QObject* parent = nullptr );
    JsImportInfo( const QString& importFile, const QJSValue& jsValue, QObject* parent = nullptr );

public:
    QString Name;
    QString File;
    QString PrepareFunction;
    QString ImportFunction;
};

#endif // JSIMPORTINFO_H
