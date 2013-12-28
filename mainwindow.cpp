#include "mainwindow.h"
#include <QScriptEngine>
#include <QFile>
#include <QDebug>
#include <QListView>
#include <QHBoxLayout>
#include <QStringListModel>
#include <QJSEngine>
#include <QQmlEngine>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    importsListView = new QListView( this );
    importsListView->setEditTriggers( QAbstractItemView::NoEditTriggers );

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
    //QJSEngine scriptEngine;
    QJSEngine scriptEngine;

    QString fileName = "importsRunner.js";
    QString contents;

    {
        QFile scriptFile( fileName );
        if( !scriptFile.open( QIODevice::ReadOnly ) )
            qDebug() << "fail to open file \"" << fileName << "\"";

        QTextStream stream( &scriptFile );
        contents = stream.readAll();

        scriptFile.close();
    }

    QJSValue ret = scriptEngine.evaluate( contents, fileName );
    if( ret.isError() )
    {
        qDebug() << "uncaught exception at line" << ret.toString();
    }


    QJSValue availableImports = scriptEngine.evaluate( "getAvailableImports()" );

    if( availableImports.isError() )
    {
        qDebug() << "uncaught exception at line" << availableImports.toString();
    }

    QStringList imports;

    qint32 count = availableImports.property( "length" ).toInt();

    for( qint32 i = 0; i < count; i++ )
        imports << availableImports.property(i).toString().toLocal8Bit();

    importsListView->setModel( new QStringListModel( imports, this ) );
}

void MainWindow::runImport( const QString& import )
{
    QJSEngine scriptEngine;

    QString fileName = "importsRunner.js";
    QString contents;

    {
        QFile scriptFile( fileName );
        if( !scriptFile.open( QIODevice::ReadOnly ) )
            qDebug() << "fail to open file \"" << fileName << "\"";

        QTextStream stream( &scriptFile );
        contents = stream.readAll();

        scriptFile.close();
    }

    QJSValue root = scriptEngine.evaluate( contents, fileName );
    QJSValue runImportFunction = scriptEngine.globalObject().property( "runImport" );

    QJSValue res = runImportFunction.call( QJSValueList() << import );

    if( res.isError() )
    {
        qDebug() << "uncaught exception at line" << res.toString();
    }

    qDebug() << res.toString();

}

void MainWindow::onImportDblClicked( const QModelIndex& index )
{
//    qDebug() << index.row() << importsListView->model()->data( index ).toString();
    runImport( importsListView->model()->data( index ).toString() );
}
