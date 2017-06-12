#ifndef QNOTES_H
#define QNOTES_H

#include "Notes.h"
#include "FenetrePrincipale.h"
#include <QtWidgets>

class FenetrePrincipale;

class QNoteReduite : public QPushButton{
    Q_OBJECT
    Note& note;
    FenetrePrincipale* fenetre;
public:
    explicit QNoteReduite(Note& n, FenetrePrincipale* f, QWidget* parent = nullptr);
signals:

public slots:
    void onClicked();
};


class QNote : public QWidget{
    Q_OBJECT
    Note& note;
public:
    explicit QNote(Note& n, QWidget *parent = nullptr);
signals:

public slots:
   void editNote();
   void supprimerNote();
};

#endif // QNOTES_H
