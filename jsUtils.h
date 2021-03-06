#ifndef JSUTILS_H
#define JSUTILS_H

#include <QObject>
#include <QJSValue>

class OmpApiJsUtils : public QObject
{
    Q_OBJECT

public:
    OmpApiJsUtils( QObject* parent = nullptr );

    Q_INVOKABLE QJSValue chooseFile();
    Q_INVOKABLE QJSValue readFile( const QString& path );

    Q_INVOKABLE void sleep( int miliseconds );

signals:
    void log( const QString& msg );
};

#endif // JSUTILS_H
