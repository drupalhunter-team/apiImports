#include "mainwindow.h"
#include <QApplication>
#include "Login.h"

int main( int argc, char *argv[] )
{
    QApplication app( argc, argv );
    app.setOrganizationName( "Omega Software" );

    LoginDialog login;
    login.exec();

    if( !login.succeeded() )
        return 0;

    MainWindow w;
    w.show();
    
    return app.exec();
}
