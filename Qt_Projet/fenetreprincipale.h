/*

#ifndef FENETREPRINCIPALE_H
#define FENETREPRINCIPALE_H


#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QLineEdit>
#include <QDateTimeEdit>
#include <QFormLayout>
#include <QLayout>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QDockWidget>
#include <QTabWidget>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QMdiArea>
#include "PluriNotes.h"
//#include "windowrelation.h"
//#include "note.h"

class fenetreprincipale : public QMainWindow
{
    Q_OBJECT

    QWidget *zoneCentrale;
    QDockWidget *zoneGauche;
    QDockWidget *zoneDroite;

    QLineEdit *titreNote;
    QDateTimeEdit *dateCreaNote;
    QTextEdit *contenuNote;
    QPushButton *enregistrer;

    QLineEdit *idNote ;
    QPushButton *boutonAfficher;
    QPushButton *boutonRestaurer;

    QFormLayout *layoutAffich;
    QVBoxLayout *layoutAffichage;
    QFormLayout *layout;
    QVBoxLayout *layoutRecherche;
    QVBoxLayout *layoutPrincipal;

public:
    explicit fenetreprincipale(QWidget *parent = 0);

signals:

public slots:
    void Recherche();
    void nouvelleFen();
    void viderLaCorbeille(){NoteManager::getInstance().viderCorbeille();}
    void quitter();
    void Restaurer();
};


#endif // FENETREPRINCIPALE_H

*/