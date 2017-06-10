#ifndef QNOTES_H
#define QNOTES_H

#include "Notes.h"
#include <QtWidgets>

class QNote : public QWidget{
    Q_OBJECT
    Note& note;
public:
    explicit QNote(Note& n, QWidget *parent = nullptr);
signals:

public slots:
};

#endif // QNOTES_H
