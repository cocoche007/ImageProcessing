//------------------------------------------------------------------------------
//! @file main.cpp
//! @brief Fichier où la fonction principale est définie
//! @author Fabrice Cochet
//! @version 1.0
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Include(s) :

#include <QApplication>
#include "MainWindow.h"

//------------------------------------------------------------------------------
//! Constructeur d'objet MainWindow
//!
//! @param argc : Le nombre d'arguments
//! @param argv : La liste d'arguments
//!
//! @return 0 si OK
//! @return <>0 sinon
//------------------------------------------------------------------------------
int main( int argc, char *argv[])
{
    QApplication application( argc, argv);
    MainWindow   mainWindow;

    mainWindow.move( 0, 0);
    mainWindow.show();
    
    return application.exec();
}
