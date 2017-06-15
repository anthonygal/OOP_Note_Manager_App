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
    QDockWidget* leftDockWidget;

    QNote *notePrincipale;
    QScrollArea *autresVersions;
    QWidget* zoneCentrale;
    QVBoxLayout* centralLayout;

    QDockWidget* rightDockWidget;
        QScrollArea *scrollRelAsc;
        QScrollArea *scrollRelDesc;

public:
    explicit FenetrePrincipale(QWidget *parent = nullptr);
    void updateNotePrincipale(Note& n);
    void updateAutresVersions(Note& n);
    void updateScrollRelAsc(Note& n);
    void updateScrollRelDesc(Note& n);

signals:

public slots:
    void changerNotePrincipale(Note& n);
    void editRelation();

};

#endif // FENETREPRINCIPALE_H
