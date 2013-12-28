#include "jsUtils.h"
#include <QFileDialog>

OmpApiJsUtils::OmpApiJsUtils( QObject* parent )
    : QObject( parent )
{ }

QJSValue OmpApiJsUtils::chooseFile()
{
    QString filePath = QFileDialog::getOpenFileName( nullptr, tr("Choose file") );
    return filePath;
}

