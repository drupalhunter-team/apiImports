#include "Login.h"
#include <QLineEdit>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include "apiCalls.h"
#include "jsUtils.h"


LoginDialog::LoginDialog( QWidget* parent )
    : QDialog( parent )
{
    serverEdit = new QLineEdit( this );
    userEdit = new QLineEdit( this );;
    passwordEdit = new QLineEdit( this );;

    serverEdit->setText( "http://localhost:8080");
    userEdit->setText( "work");
    passwordEdit->setText( "work" );

    QLabel* serverLabel = new QLabel( tr( "Server" ), this );
    QLabel* userLabel = new QLabel( tr( "User" ), this );
    QLabel* passwordLabel = new QLabel( tr( "Password" ), this );

    QPushButton* okBtn = new QPushButton( tr( "Ok" ), this );
    QPushButton* cancelBtn = new QPushButton( tr( "Cancel" ), this );

    QGridLayout* layout = new QGridLayout( this );

    layout->addWidget( serverLabel  , 0, 0, Qt::AlignRight );
    layout->addWidget( serverEdit   , 0, 1 );
    layout->addWidget( userLabel    , 1, 0, Qt::AlignRight );
    layout->addWidget( userEdit     , 1, 1 );
    layout->addWidget( passwordLabel, 2, 0, Qt::AlignRight );
    layout->addWidget( passwordEdit , 2, 1 );

    QHBoxLayout* okCancelLayout = new QHBoxLayout();
    okCancelLayout->addWidget( okBtn );
    okCancelLayout->addWidget( cancelBtn );

    layout->addLayout( okCancelLayout, 3, 0, 1, 2, Qt::AlignRight );

    QObject::connect( okBtn, SIGNAL(clicked()), this, SLOT(doLogin()) );
    QObject::connect( cancelBtn, SIGNAL(clicked()), this, SLOT(close()) );
}

bool LoginDialog::succeeded()
{
    return !_authToken.isEmpty();
}

QString LoginDialog::authToken()
{
    return _authToken;
}

void LoginDialog::doLogin()
{
    _authToken = "";

    OmpApiCalls apiCalls;

    QString url = serverEdit->text() + "/login.getAuthToken";

    QJsonObject params;
    params.insert( "login", QJsonValue( userEdit->text() ) );
    params.insert( "password", QJsonValue( passwordEdit->text() ) );

    QJsonObject res = apiCalls.callSync( url, params );

    QString errStr;
    if( !apiCalls.isSucceded( res, errStr ) )
    {
        QMessageBox msgBox;
        msgBox.setText( errStr );

        msgBox.exec();
        return;
    }

    if( !res[ "authToken" ].isString() )
        Q_ASSERT( false );

    _authToken = res[ "authToken" ].toString();
    close();
}
