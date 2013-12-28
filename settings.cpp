#include "settings.h"
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QDebug>
#include <QFileDialog>
#include <QSettings>
#include <QCoreApplication>

ImportAppSettingDialog::ImportAppSettingDialog( QWidget *parent )
    : QDialog( parent )
{
    settings = new QSettings( QSettings::IniFormat, QSettings::UserScope, QCoreApplication::instance()->organizationName(), QCoreApplication::instance()->applicationName(), this );

    QLabel* label = new QLabel( tr("Path to scripts: "), this );

    pathEdit = new QLineEdit( this );
    pathEdit->setReadOnly( true );
    pathEdit->setText( settings->value( "scriptPath", "" ).toString() );

    QPushButton* choosePathBtn = new QPushButton( tr("..."), this );
    QObject::connect( choosePathBtn, SIGNAL(clicked(bool)), this, SLOT(onChooseScriptPathClicked()) );

    QHBoxLayout* layout = new QHBoxLayout( this );
    layout->addWidget( label );
    layout->addWidget( pathEdit );
    layout->addWidget( choosePathBtn );

    setLayout( layout );
}

void ImportAppSettingDialog::onChooseScriptPathClicked()
{
    QString dir = QFileDialog::getExistingDirectory( this, tr("Choose directory with import scripts"), "", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks );

    settings->setValue( "scriptPath", dir );
    pathEdit->setText( settings->value( "scriptPath", "" ).toString() );
}
