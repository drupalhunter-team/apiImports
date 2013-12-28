#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QListView;
class QSettings;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void initImportsListView();
    void runImport( const QString& import );

private slots:
    void openSettings();
    void onImportDblClicked( const QModelIndex& index );

private:
    QListView* importsListView;
    QSettings* settings;
};

#endif // MAINWINDOW_H
