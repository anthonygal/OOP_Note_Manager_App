#ifndef FENETREPRINCIPALE_H
#define FENETREPRINCIPALE_H

#include "Manager.h"
#include "QNotes.h"
#include <QtWidgets>
#include <QHBoxLayout>
#include <QVBoxLayout>

class QNote;

class FenetrePrincipale : public QMainWindow{
    Q_OBJECT
    Manager& manager;
    QNote* notePrincipale;
    //QFrame* anciennesVersions;
public:
    explicit FenetrePrincipale(QWidget *parent = nullptr);
    void updateCentralWidget(Note& n);

signals:

public slots:
    void changerNotePrincipale(Note& n);

};

#endif // FENETREPRINCIPALE_H
