#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QTableView;
class QTextEdit;
class QSettings;
class JsImportInfo;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void initImportsListView();
    void runImport( const JsImportInfo* importInfo );

private slots:
    void openSettings();
    void onImportDblClicked( const QModelIndex& index );
    void appendLog( const QString& msg );

private:
    QTableView* importsView;
    QSettings* settings;
    QTextEdit* logView;
};

#endif // MAINWINDOW_H
