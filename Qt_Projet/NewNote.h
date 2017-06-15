#ifndef NEWNOTE_H
#define NEWNOTE_H

#include <QtWidgets>

class NewNote : public QWidget
{
    Q_OBJECT
protected:
    QVBoxLayout* layer;

        QHBoxLayout* titreLayout;
            QLabel* titreLab;
            QLineEdit* titre;

        QHBoxLayout* boutonLayout;
            QPushButton* enregistrer;
            QPushButton* annuler;
public:
    explicit NewNote(QWidget *parent = nullptr);
    virtual ~NewNote(){}
signals:

public slots:
    virtual void enregistrerNote()=0;
};

class NewArticle : public NewNote
{
    Q_OBJECT
    QHBoxLayout* texteLayout;
        QLabel* texteLab;
        QTextEdit* texte;
public:
    explicit NewArticle(QWidget *parent = nullptr);
signals:

public slots:
    void enregistrerNote();
};

class NewTache : public NewNote
{
    Q_OBJECT
    QHBoxLayout* actionLayout;
        QLabel* actionLab;
        QTextEdit* action;

    QHBoxLayout* prioriteLayout;
        QLabel* prioriteLab;
        QSpinBox* priorite;

    QHBoxLayout* echeanceLayout;
        QLabel* echeanceLab;
        QCalendarWidget* echeance;
public:
    explicit NewTache(QWidget *parent = nullptr);
signals:

public slots:
    void enregistrerNote();
};

class NewMultimedia : public NewNote
{
    Q_OBJECT
    QHBoxLayout* descLayout;
        QLabel* descLab;
        QTextEdit* desc;

    QHBoxLayout* adresseLayout;
        QLabel* adresseLab;
        QLabel* adresse;
        QPushButton* parcourir;

    QGroupBox* type;
        QHBoxLayout *hbox ;
            QLabel* typeLab;
            QRadioButton* Image;
            QRadioButton* Audio;
            QRadioButton* Video;
public:
    explicit NewMultimedia(QWidget *parent = nullptr);
signals:

public slots:
    void modifierAdresse();
    void enregistrerNote();
};

#endif // NEWNOTE_H
