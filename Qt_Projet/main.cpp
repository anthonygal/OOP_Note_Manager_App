//#include "timing.h"
#include "Notes.h"
#include "NoteEditeur.h"
#include "FenetrePrincipale.h"
#include <QFile>
#include <QFileDialog>
#include <QApplication>

#include <QString>
#include <string>
#include <iostream>

int main()
{
        std::cout << "Hello world!" << std::endl;
        return 0;
}



int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    Manager& m=Manager::donneInstance();
    //QString fichier = QFileDialog::getOpenFileName();
    //m.setFilename(fichier);
    m.setFilename("notes2.xml");

    try{
        m.load();
    }catch(NoteException e){qDebug()<<e.getInfo()<<"\n";}


    FenetrePrincipale& fenetre = FenetrePrincipale::donneInstance();
    fenetre.show();








    return app.exec();
}
