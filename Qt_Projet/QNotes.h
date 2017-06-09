#ifndef QNOTES_H
#define QNOTES_H

#include "Notes.h"
#include <QtWidgets>

class QNote : public QWidget{
    Q_OBJECT
    Note& note;
protected:
    QVBoxLayout* partieNote;
public:
    explicit QNote(Note& n, QWidget *parent = nullptr);
    QVBoxLayout* getLayout() const {return partieNote;}
signals:

public slots:
};

//class QArticle : public QNote{
//    Q_OBJECT
//    Article& article;
//public:
//    explicit QArticle(Article& a, QWidget *parent = nullptr);

//signals:

//public slots:
//};
#endif // QNOTES_H
