#ifndef JSIMPORTTHREAD_H
#define JSIMPORTTHREAD_H

#include <QThread>
#include <QJsonObject>

class JsImportDialog;
class JsImportInfo;

class JsImportEngine;

class JsImportThread : public QThread
{
    Q_OBJECT

public:
    explicit JsImportThread( const JsImportInfo* info, QObject *parent = nullptr );
//    explicit JsImportThread( QThread* guiThread, JsImportDialog* importDlg, const JsImportInfo* importInfo, QObject *parent = nullptr );

    void setImportPrepareResults( const QJsonObject& prepareResults );
    void setImportDialogProgressWidget( const JsImportDialog* importDlg );

    QThread* getGuiThread();

protected:
    virtual void run();

//private slots:
//    void appendLog( const QString& msg );

signals:
    void appendLog( const QString& msg );
    void setProgressMaximum( int maximum );
    void setProgressValue( int maximum );

private:
    const JsImportDialog* _importProgressWidget;
    QThread* _guiThread;
    const JsImportInfo* _jsImportInfo;
    QJsonObject _prepareResults;

//    JsImportEngine* _engine;
};

#endif // JSIMPORTTHREAD_H
