#ifndef QNOTES_H
#define QNOTES_H

#include "Notes.h"
#include "FenetrePrincipale.h"
#include <QtWidgets>

class FenetrePrincipale;

class QNoteReduite : public QPushButton{
    Q_OBJECT
    Note& note;
public:
    explicit QNoteReduite(Note& n, QWidget* parent = nullptr);
    Note& getNote() const {return note;}
    unsigned long getID() const {return note.getID();}
    QString getTitre() const {return note.getTitre();}
    QString getTypeNote() const {return note.getTypeNote();}
signals:

public slots:
    void onClicked();
};


class QNote : public QFrame{
    Q_OBJECT
    Note& note;
public:
    explicit QNote(Note& n, QWidget *parent = nullptr);
    Note& getNote() const {return note;}
    unsigned long getID() const {return note.getID();}
    QString getTitre() const {return note.getTitre();}
    const QDateTime& getDateCrea() const {return note.getDateCrea();}
    const QDateTime& getDateModif() const {return note.getDateModif();}
    NoteEtat getEtat() const {return note.getEtat();} /**< etat vaut 0 pour active, 1 pour archivee et 2 pour corbeille */
    bool isActuelle() const {return note.isActuelle();}
    QString getTypeNote() const {return note.getTypeNote();}
signals:

public slots:
   void editer();
   void supprimer();
   void restaurerVersion();
   void restaurerNote();
   void tacheEnAttente();
   void tacheTerminee();
   void tacheReprise();
};

#endif // QNOTES_H
