#ifndef FENETREPRINCIPALE_H
#define FENETREPRINCIPALE_H

#include "Manager.h"
#include "QNotes.h"
#include <QtWidgets>
#include <QHBoxLayout>
#include <QVBoxLayout>

class FenetrePrincipale : public QMainWindow{
    Q_OBJECT
    Manager& manager;
    //Note& note;
public:
    explicit FenetrePrincipale(Manager& m, QWidget *parent = nullptr);

signals:

public slots:

};

#endif // FENETREPRINCIPALE_H
