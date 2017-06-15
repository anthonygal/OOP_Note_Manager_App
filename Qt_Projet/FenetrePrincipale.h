#ifndef FENETREPRINCIPALE_H
#define FENETREPRINCIPALE_H

#include "Manager.h"
#include "QNotes.h"
#include "relationediteur.h"
#include <QtWidgets>
#include <QHBoxLayout>
#include <QVBoxLayout>

class FenetrePrincipale : public QMainWindow{
    Q_OBJECT
    static FenetrePrincipale* instanceUnique;

    QDockWidget* leftDockWidget;
        QScrollArea *scrollAreaActives;
        QScrollArea *scrollTachesTriees;
        QScrollArea *scrollAreaArchivees;

    QWidget *notePrincipale;
    QScrollArea *autresVersions;
    //QWidget* zoneCentrale;
    //QVBoxLayout* centralLayout;

    QDockWidget* rightDockWidget;
        QScrollArea *scrollRelAsc;
        QScrollArea *scrollRelDesc;

    explicit FenetrePrincipale(QWidget *parent = nullptr);
public:
    /* Template Method Singleton */
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
signals:

public slots:
    void reaffichageNote();
    void updateFenetre(Note& n);
    void updateFenetre();
    void sauvegarder();
    void newArticle();
    void newTache();
    void newMultimedia();
    void voirRelations();
    void editRelation();
    void createRelation();
    void viderCorbeille();
    void restaurerCorbeille();
};

#endif // FENETREPRINCIPALE_H
