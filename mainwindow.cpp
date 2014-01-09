#include "mainwindow.h"
#include <QScriptEngine>
#include <QFile>
#include <QDebug>
#include <QTableView>
#include <QHeaderView>
#include <QVBoxLayout>
#include <QStringListModel>
#include <QJSEngine>
#include <QQmlEngine>
#include <QMenuBar>
#include <QDir>
#include <QSettings>
#include <QCoreApplication>
#include <QDirModel>
#include <QTextEdit>
#include <QProgressBar>
#include "apiCalls.h"
#include "settings.h"
#include "jsUtils.h"
#include "JsImportInfo.h"
#include "JsImportsModel.h"
#include "JsImportThread.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    settings = new QSettings( QSettings::IniFormat, QSettings::UserScope, QCoreApplication::instance()->organizationName(), QCoreApplication::instance()->applicationName(), this );

    importsView = new QTableView( this );
    importsView->setEditTriggers( QAbstractItemView::NoEditTriggers );
    importsView->horizontalHeader()->setSectionsMovable( true );

    logView = new QTextEdit( this );
    logView->setReadOnly( true );

    QAction* settingsAct = new QAction( tr("&Settings..."), this );
    QObject::connect( settingsAct, SIGNAL(triggered()), this, SLOT(openSettings()) );

    QMenu* toolsMenu = menuBar()->addMenu( tr("&Tools") );
    toolsMenu->addAction( settingsAct );


    QObject::connect( importsView, SIGNAL( doubleClicked(const QModelIndex&)), this, SLOT( onImportDblClicked(const QModelIndex&) ) );

    initImportsListView();

    QVBoxLayout* layout = new QVBoxLayout( this );
    layout->addWidget( importsView );
    layout->addWidget( logView );

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

    QList<JsImportInfo*> jsImports;

    for( int i = 0; i < jsFiles.size(); i++ )
    {
        QJSEngine engine;

        {
            QString contents;
            QFile scriptFile( path + "/" + jsFiles[i] );
            if( !scriptFile.open( QIODevice::ReadOnly ) )
            {
                qDebug() << "Fail to open file \"" << jsFiles[i] << "\"";
                continue;
            }

            QTextStream stream( &scriptFile );
            contents = stream.readAll();

            scriptFile.close();

            QJSValue ret = engine.evaluate( contents, jsFiles[i] );
            if( ret.isError() )
            {
                qDebug() << "Uncaught exception: " << ret.toString();
                continue;
            }

            QJSValue avImports = engine.globalObject().property( "availibleImports" );
            if( avImports.isUndefined() )
                continue;

            Q_ASSERT( avImports.isArray() );

            int length = avImports.property( "length" ).toInt();
            for( long j = 0; j < length; j++ )
            {
                QJSValue jsImportVal = avImports.property( j );

                JsImportInfo* importInfo = new JsImportInfo( jsImportVal, this );
                importInfo->File = path + "/" + jsFiles[i];

                jsImports << importInfo;
            }
        }
    }

    importsView->setModel( new JsImportsModel( jsImports, this ) );
}

void MainWindow::runImport( const QString& file, const QString& function )
{
    QProgressBar* progressBar = new QProgressBar();

    JsImportThread *importThread = new JsImportThread( progressBar, file, function, this );

    connect( importThread, &JsImportThread::finished, importThread, &QObject::deleteLater );
    connect( importThread, &JsImportThread::finished, progressBar, &QWidget::close );
    connect( importThread, &JsImportThread::appendLog, this, &MainWindow::appendLog );
    connect( importThread, &JsImportThread::setProgressMaximum, progressBar, &QProgressBar::setMaximum );
    connect( importThread, &JsImportThread::setProgressValue, progressBar, &QProgressBar::setValue );

    progressBar->show();
    importThread->start();
}

void MainWindow::openSettings()
{
    ImportAppSettingDialog* settingsDlg = new ImportAppSettingDialog( this );
    settingsDlg->setModal( true );
    settingsDlg->show();
}

void MainWindow::onImportDblClicked( const QModelIndex& index )
{
    QAbstractItemModel* model = importsView->model();

    QModelIndex fileIndex = model->index( index.row(), JsImportsModel::HidFile );
    QModelIndex fnIndex = model->index( index.row(), JsImportsModel::HidFunction );

    runImport( model->data( fileIndex ).toString(), model->data( fnIndex ).toString() );
}

void MainWindow::appendLog( const QString& msg )
{
    logView->append( msg );
}
