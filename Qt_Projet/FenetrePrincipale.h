#ifndef FENETREPRINCIPALE_H
#define FENETREPRINCIPALE_H

#include "Manager.h"
#include "QNotes.h"
#include "relationediteur.h"
#include <QtWidgets>
#include <QHBoxLayout>
#include <QVBoxLayout>

class QNote;

class FenetrePrincipale : public QMainWindow{
    Q_OBJECT
    static FenetrePrincipale* instanceUnique;

    QDockWidget* leftDockWidget;
        QScrollArea *scrollAreaActives;
        QScrollArea *scrollTachesTriees;
        QScrollArea *scrollAreaArchivees;

    //QNote *notePrincipale;
    QWidget *notePrincipale;
    QScrollArea *autresVersions;
    QWidget* zoneCentrale;
    QVBoxLayout* centralLayout;

    QDockWidget* rightDockWidget;
        QScrollArea *scrollRelAsc;
        QScrollArea *scrollRelDesc;

    explicit FenetrePrincipale(QWidget *parent = nullptr);
    ~FenetrePrincipale();
public:
     QDockWidget* getleftDockWidget(){return leftDockWidget;}
     QNote* getnotePrincipale() {return notePrincipale;}
     QDockWidget* getrightDockWidget(){return getrightDockWidget();}
     QVBoxLayout* getcentralLayout(){return centralLayout;}
     QScrollArea* getautresVersions() {return autresVersions;}
     QWidget* getzoneCentrale() {return zoneCentrale;}
    /**< Template Method Singleton */
    static FenetrePrincipale& donneInstance();
    static void libereInstance();

    void updateScrollAreaActives();
    void updateTachesTriees();
    void updateScrollAreaArchivees();
    void updateNotePrincipale(Note& n);
    void updateNotePrincipale();
    void updateAutresVersions(Note& n);
    void updateAutresVersions();
    void updateScrollRelAsc(Note& n);
    void updateScrollRelAsc();
    void updateScrollRelDesc(Note& n);
    void updateScrollRelDesc();
    
    void reaffichageNote();
signals:

public slots:

  //  void changerNotePrincipale(Note& n);
    void editRelation();
    void createRelation();

    void updateFenetre(Note& n);
    void updateFenetre();
    void viderCorbeille();
    void sauvegarder();
    void newArticle();
    void newTache();
    void newMultimedia();
};

#endif // FENETREPRINCIPALE_H
