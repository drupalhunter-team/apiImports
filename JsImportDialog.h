#ifndef JSIMPORTDIALOG_H
#define JSIMPORTDIALOG_H

#include <QDialog>

class QProgressBar;
class QLabel;

class JsImportDialog : public QDialog
{
    Q_OBJECT

public:
    JsImportDialog( QWidget *parent = 0 );

public slots:
    void setName1( const QString& name );
    void setMaximum1( int maximum );
    void setValue1( int value );

    void setName2( const QString& name );
    void setMaximum2( int maximum );
    void setValue2( int value );

private:
    QLabel* labelName1;
    QLabel* labelName2;
    QProgressBar* progressBar1;
    QProgressBar* progressBar2;
};

class JsImportProgress : public QObject
{
    Q_OBJECT

public:
    JsImportProgress( JsImportDialog* importDlg, QObject *parent = nullptr );

/*    Q_INVOKABLE void setName1( const QString& name );
    Q_INVOKABLE void setMaximum1( int maximum );
    Q_INVOKABLE void setValue1( int value );

    Q_INVOKABLE void setName2( const QString& name );
    Q_INVOKABLE void setMaximum2( int maximum );
    Q_INVOKABLE void setValue2( int value );
*/

signals:
    void setName1( const QString& name );
    void setMaximum1( int maximum );
    void setValue1( int value );

    void setName2( const QString& name );
    void setMaximum2( int maximum );
    void setValue2( int value );

private:
    JsImportDialog* jsImportDialog;
};

#endif // JSIMPORTDIALOG_H
