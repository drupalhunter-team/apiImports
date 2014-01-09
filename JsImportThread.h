#ifndef JSIMPORTTHREAD_H
#define JSIMPORTTHREAD_H

#include <QThread>

class QProgressBar;

class JsImportThread : public QThread
{
    Q_OBJECT

public:
    explicit JsImportThread( QProgressBar* progressBar, const QString& file, const QString& function, QObject *parent = nullptr );

protected:
    virtual void run();

//private slots:
//    void appendLog( const QString& msg );

signals:
    void appendLog( const QString& msg );
    void setProgressMaximum( int maximum );
    void setProgressValue( int maximum );

private:
    QString jsFile;
    QString jsFunction;
    QProgressBar* importProgressBar;
};

#endif // JSIMPORTTHREAD_H
