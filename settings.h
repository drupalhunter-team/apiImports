#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>

class QLineEdit;
class QSettings;

class ImportAppSettingDialog : public QDialog
{
    Q_OBJECT

public:
    ImportAppSettingDialog( QWidget *parent = 0 );

private slots:
    void onChooseScriptPathClicked();

private:
    QLineEdit* pathEdit;
    QSettings* settings;
};

#endif // SETTINGS_H
