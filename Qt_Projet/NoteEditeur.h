#ifndef NOTEEDITEUR_H
#define NOTEEDITEUR_H

#include "Notes.h"
#include <QtWidgets>
#include <QItemSelectionModel>

class Note;
class Article;
class Tache;
class Multimedia;

class NoteEditeur : public QWidget
{
    Q_OBJECT
protected:
    Note& note;

    QVBoxLayout* layer;
        QHBoxLayout* IDLayout;
            QLabel* IDLab;
            QLineEdit* ID;
        QHBoxLayout* titreLayout;
            QLabel* titreLab;
            QLineEdit* titre;
        QHBoxLayout* datesLayout;
            QLabel* dateCreaLab;
            QDateTimeEdit* dateCrea;
            QLabel* dateModifLab;
            QDateTimeEdit* dateModif;
        QHBoxLayout* boutonLayout;
            QPushButton* enregistrer;
            QPushButton* annuler;

public:
    NoteEditeur(Note &n, QWidget* parent = nullptr);
    virtual ~NoteEditeur(){}
signals:

public slots:
    void activerEnregistrer();
    virtual void enregistrerNote()=0;
};


class ArticleEditeur : public NoteEditeur {
    Q_OBJECT
private:
    Article& article;

    QHBoxLayout* texteLayout;
        QLabel* texteLab;
        QTextEdit* texte;

public:
    explicit ArticleEditeur(Article& a, QWidget* parent=0);
    ~ArticleEditeur(){}
signals:

public slots:
    void enregistrerNote();


};

class TacheEditeur : public NoteEditeur {
    Q_OBJECT
private:
    Tache& tache;

    QHBoxLayout* actionLayout;
        QLabel* actionLab;
        QTextEdit* action;

    QHBoxLayout* echeanceLayout;
        QLabel* echeanceLab;
        QCalendarWidget* echeance;

    QHBoxLayout* prioriteLayout;
        QLabel* prioriteLab;
        QSpinBox* priorite;

public:
    explicit TacheEditeur(Tache& t, QWidget* parent=0);
    ~TacheEditeur(){}
signals:

public slots:
    void enregistrerNote();
};

class MultimediaEditeur: public NoteEditeur {
    Q_OBJECT
private:
    Multimedia& multimedia;

    QHBoxLayout* descLayout;
        QLabel* descLab;
        QTextEdit* desc;

    QHBoxLayout* adresseLayout;
        QLabel* adresseLab;
        QLineEdit* adresse;

    QGroupBox* type;
        QHBoxLayout *hbox ;
            QLabel* typeLab;
            QRadioButton* Image;
            QRadioButton* Audio;
            QRadioButton* Video;

public:
    explicit MultimediaEditeur(Multimedia& t, QWidget* parent=0);
    ~MultimediaEditeur(){}
signals:

public slots:
void enregistrerNote();
};

#endif // NOTEEDITEUR_H

