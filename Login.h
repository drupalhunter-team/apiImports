#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>

class QLineEdit;

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    LoginDialog( QWidget* parent = nullptr );

    bool succeeded();

    QString authToken();

private slots:
    void doLogin();

private:
    QLineEdit* serverEdit;
    QLineEdit* userEdit;
    QLineEdit* passwordEdit;

    QString _authToken;
};

#endif // LOGIN_H
