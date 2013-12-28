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
};

#endif // JSUTILS_H
