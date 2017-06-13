#ifndef NOTEEDITEUR_H
#define NOTEEDITEUR_H

#include "Notes.h"
#include <QtWidgets>
#include <QItemSelectionModel>

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
    //friend class Manager;
protected:
    /** Edit */
    QLineEdit* ID;
    QLineEdit* titre;
    QDateEdit* dateCrea;
    QDateEdit* dateModif;

    /** Bouton */
    QPushButton* enregistrer;
    QPushButton* annuler;


    /** Layout H */
    QHBoxLayout* IDLayout;
    QHBoxLayout* titreLayout;
    QHBoxLayout* datesLayout;
    QHBoxLayout* boutonLayout;

    /** Label */
    QLabel* IDLab;
    QLabel* titreLab;
    QLabel* dateCreaLab;
    QLabel* dateModifLab;

    /** Layout V */
    QVBoxLayout* layer;

    //bool isSaved;

public:
    virtual ~NoteEditeur(){}
    NoteEditeur(Note& n, QWidget* parent=0);
    virtual void activerEnregistrer();

signals:

public slots:
    virtual void enregistrerNote()=0;
};


class ArticleEditeur : public NoteEditeur {
private:
    Q_OBJECT
        Article& article;

        QTextEdit* texte;
        QLabel* texteLab;
        QHBoxLayout* texteLayout;

public:
      explicit ArticleEditeur(Article& a, QWidget* parent=0);
signals:

public slots:
        void enregistrerNote();


};

class TacheEditeur : public NoteEditeur {
private:
    Q_OBJECT
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
signals:

public slots:
    void enregistrerNote();

};

class MultimediaEditeur: public NoteEditeur {
private:
    Q_OBJECT
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
signals:

public slots:
void enregistrerNote();
};

#endif // NOTEEDITEUR_H

