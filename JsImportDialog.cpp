#include "JsImportDialog.h"
#include <QProgressBar>
#include <QVBoxLayout>
#include <QLabel>

JsImportDialog::JsImportDialog( QWidget *parent )
    : QDialog( parent )
{
    labelName1 = new QLabel( "", this );
    labelName2 = new QLabel( "", this );
    progressBar1 = new QProgressBar( this );
    progressBar2 = new QProgressBar( this );

    QVBoxLayout* layout = new QVBoxLayout( this );
    layout->addWidget( labelName1 );
    layout->addWidget( progressBar1 );
    layout->addWidget( labelName2 );
    layout->addWidget( progressBar2 );
}

void JsImportDialog::setName1( const QString& name )
{
    labelName1->setText( name );
}

void JsImportDialog::setMaximum1( int maximum )
{
    progressBar1->setMaximum( maximum );
}

void JsImportDialog::setValue1( int value )
{
    progressBar1->setValue( value );
}

void JsImportDialog::setName2( const QString& name )
{
    labelName2->setText( name );
}

void JsImportDialog::setMaximum2( int maximum )
{
    progressBar2->setMaximum( maximum );
}

void JsImportDialog::setValue2( int value )
{
    progressBar2->setValue( value );
}

///////////////////////////////////////////////////////////////////////////////
JsImportProgress::JsImportProgress( const JsImportDialog* importDlg, QObject *parent )
    : QObject( parent )
{
    jsImportDialog = importDlg;

    connect( this, &JsImportProgress::setName1   , importDlg, &JsImportDialog::setName1 );
    connect( this, &JsImportProgress::setMaximum1, importDlg, &JsImportDialog::setMaximum1 );
    connect( this, &JsImportProgress::setValue1  , importDlg, &JsImportDialog::setValue1 );
    connect( this, &JsImportProgress::setName2   , importDlg, &JsImportDialog::setName2 );
    connect( this, &JsImportProgress::setMaximum2, importDlg, &JsImportDialog::setMaximum2 );
    connect( this, &JsImportProgress::setValue2  , importDlg, &JsImportDialog::setValue2 );
}

/*void JsImportProgress::setName1( const QString& name )
{
}

void JsImportProgress::setMaximum1( int maximum )
{
}

void JsImportProgress::setValue1( int value )
{
}

void JsImportProgress::setName2( const QString& name )
{
}

void JsImportProgress::setMaximum2( int maximum )
{
}

void JsImportProgress::setValue2( int value )
{
}
*/
