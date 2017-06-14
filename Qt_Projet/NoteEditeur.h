#ifndef NOTEEDITEUR_H
#define NOTEEDITEUR_H

#include "Notes.h"
#include <QtWidgets>
#include <QItemSelectionModel>

class Note;
class Article;
class Tache;
class Multimedia;

//class NewNote : public QWidget{
//    Q_OBJECT
//    Note& note;
//public:
//    explicit NewNote(Note& n, QWidget *parent = nullptr);
//signals:

//public slots:
//   void editNote();
//   void supprimerNote();
//};

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
    virtual void activerEnregistrer();
    virtual void enregistrerNote()=0;
};


class ArticleEditeur : public NoteEditeur {
    Q_OBJECT
private:
    Article& article;

    QTextEdit* texte;
    QLabel* texteLab;
    QHBoxLayout* texteLayout;

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
    QTextEdit* action;
    QLineEdit* statut;
    QCalendarWidget* echeance;
    QSpinBox* priorite;

    QHBoxLayout* actionLayout;
    QHBoxLayout* statutLayout;
    QHBoxLayout* echeanceLayout;
    QHBoxLayout* prioriteLayout;

    QLabel* actionLab;
    QLabel* statutLab;
    QLabel* echeanceLab;
    QLabel* prioriteLab;

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
    QTextEdit* desc;
    QLineEdit* adresse;
    QGroupBox* type;
    QRadioButton* Image;
    QRadioButton* Audio;
    QRadioButton* Video;


    QLabel* descLab;
    QLabel* adresseLab;
    QLabel* typeLab;


    QHBoxLayout* descLayout;
    QHBoxLayout* adresseLayout;
    QHBoxLayout* typeLayout;
    QHBoxLayout *hbox ;

public:
    explicit MultimediaEditeur(Multimedia& t, QWidget* parent=0);
    ~MultimediaEditeur(){}
signals:

public slots:
void enregistrerNote();
};

#endif // NOTEEDITEUR_H

