#include "mainwindow.h"
#include <QScriptEngine>
#include <QFile>
#include <QDebug>
#include <QListView>
#include <QHBoxLayout>
#include <QStringListModel>
#include <QJSEngine>
#include <QQmlEngine>
#include <QMenuBar>
#include <QDir>
#include <QSettings>
#include <QCoreApplication>
#include "apiCalls.h"
#include "settings.h"
#include "jsUtils.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    settings = new QSettings( QSettings::IniFormat, QSettings::UserScope, QCoreApplication::instance()->organizationName(), QCoreApplication::instance()->applicationName(), this );

    importsListView = new QListView( this );
    importsListView->setEditTriggers( QAbstractItemView::NoEditTriggers );

    QAction* settingsAct = new QAction( tr("&Settings..."), this );
    QObject::connect( settingsAct, SIGNAL(triggered()), this, SLOT(openSettings()) );

    QMenu* toolsMenu = menuBar()->addMenu( tr("&Tools") );
    toolsMenu->addAction( settingsAct );

    QObject::connect( importsListView, SIGNAL( doubleClicked(const QModelIndex&)), this, SLOT( onImportDblClicked(const QModelIndex&) ) );

    initImportsListView();

    QHBoxLayout* layout = new QHBoxLayout( this );
    layout->addWidget( importsListView );

    QWidget* centralWidget = new QWidget( this );
    centralWidget->setLayout( layout );

    setCentralWidget( centralWidget );
}

MainWindow::~MainWindow()
{ }

void MainWindow::initImportsListView()
{
    QString path = settings->value( "scriptPath", "" ).toString();
    if( path.isEmpty() )
        return;

    QDir importsDir( path );

    QStringList jsFiles = importsDir.entryList( QStringList( "*.js" ), QDir::Files | QDir::NoSymLinks );

    QStringList validImportFiles;

    for( int i = 0; i < jsFiles.size(); i++ )
    {
        QJSEngine engine;

        {
            QString contents;
            QFile scriptFile( jsFiles[i] );
            if( !scriptFile.open( QIODevice::ReadOnly ) )
                qDebug() << "Fail to open file \"" << jsFiles[i] << "\"";

            QTextStream stream( &scriptFile );
            contents = stream.readAll();

            scriptFile.close();

            QJSValue ret = engine.evaluate( contents, jsFiles[i] );
            if( ret.isError() )
            {
                qDebug() << "Uncaught exception: " << ret.toString();
                continue;
            }
        }

        validImportFiles << path + "/" + jsFiles[i];
    }

    importsListView->setModel( new QStringListModel( validImportFiles, this ) );
}

void MainWindow::runImport( const QString& import )
{
    QJSEngine engine;

    {
        QString contents;

        QFile scriptFile( import );
        if( !scriptFile.open( QIODevice::ReadOnly ) )
        {
            qDebug() << "Fail to open file \"" << import << "\"";
            return;
        }

        QTextStream stream( &scriptFile );
        contents = stream.readAll();

        scriptFile.close();

        QJSValue ret = engine.evaluate( contents, import );
        if( ret.isError() )
        {
            qDebug() << "Uncaught exception: " << ret.toString();
            return;
        }
    }

    OmpApiCalls* ompApi = new OmpApiCalls();
    QJSValue ompApiValue = engine.newQObject( ompApi );

    engine.globalObject().setProperty( "API", ompApiValue );

    OmpApiJsUtils* jsUtils = new OmpApiJsUtils();
    QJSValue jsUtilsValue = engine.newQObject( jsUtils );

    engine.globalObject().setProperty( "UTILS", jsUtilsValue );

    QJSValue runImportFunction = engine.globalObject().property( "runImport" );

    QJSValue res = runImportFunction.call( QJSValueList() );

    if( res.isError() )
    {
        qDebug() << "Uncaught exception: " << res.toString();
        return;
    }

    qDebug() << res.toString();
}

void MainWindow::openSettings()
{
    ImportAppSettingDialog* settingsDlg = new ImportAppSettingDialog( this );
    settingsDlg->setModal( true );
    settingsDlg->show();
}

void MainWindow::onImportDblClicked( const QModelIndex& index )
{
//    qDebug() << index.row() << importsListView->model()->data( index ).toString();
    runImport( importsListView->model()->data( index ).toString() );
}
