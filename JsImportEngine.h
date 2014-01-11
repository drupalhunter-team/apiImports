#ifndef JSIMPORTENGINE_H
#define JSIMPORTENGINE_H

#include <QObject>
#include <QJsonObject>

class QJSEngine;
class QJSValue;
class JsImportInfo;
class JsImportDialog;

class JsImportEngine : public QObject
{
    Q_OBJECT

public:
    JsImportEngine( QObject* parent = nullptr );

    bool init( const JsImportInfo* info, QString& errStr = QString() );

    bool setImportProgressWidget( const JsImportDialog* dlg );

    bool hasPrepareFunction();
    bool runPrepareFunction( QJsonObject& prepareResults );

    bool hasImportFunction();
    bool runImportFunction( const QJsonObject& prepareResults = QJsonObject() );

signals:
    void appendLog( const QString& msg );

private:
    QJSEngine* _jsEngine;
    JsImportInfo* _jsImportInfo;
};

#endif // JSIMPORTENGINE_H
