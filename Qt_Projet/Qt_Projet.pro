QT += core
QT += widgets
QT += xml

QMAKE_CXXFLAGS = -std=c++11
QMAKE_LFLAGS = -std=c++11

HEADERS += \
    Relations.h \
    timing.h \
    NoteEditeur.h \
    FenetrePrincipale.h \
    Notes.h \
    Manager.h \
    QNotes.h \
    NewNote.h

SOURCES += \
    main.cpp \
    Relations.cpp \
    timing.cpp \
    NoteEditeur.cpp \
    FenetrePrincipale.cpp \
    Notes.cpp \
    Manager.cpp \
    QNotes.cpp \
    NewNote.cpp
