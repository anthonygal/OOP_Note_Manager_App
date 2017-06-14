#include "timing.h"
#include "Notes.h"
#include "NoteEditeur.h"
#include "FenetrePrincipale.h"
#include <QFile>
#include <QFileDialog>
#include <QApplication>

using namespace TIME;

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    Manager& m=Manager::donneInstance();
    //QString fichier = QFileDialog::getOpenFileName();
    //m.setFilename(fichier);

    m.setFilename("notes2.xml");
    m.load();

    FenetrePrincipale fenetre;
    fenetre.show();

//    Article a(1,"titre","texte");
//    ArticleEditeur* editeur = new ArticleEditeur(a);
//    editeur->show();

    return app.exec();
}
