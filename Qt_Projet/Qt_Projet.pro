QT += core
QT += widgets
QT += xml

QMAKE_CXXFLAGS = -std=c++11
QMAKE_LFLAGS = -std=c++11

HEADERS += \
    PluriNotes.h \
    Relations.h \
    timing.h \
    NoteEditeur.h \
    FenetrePrincipale.h

SOURCES += \
    main.cpp \
    PluriNotes.cpp \
    Relations.cpp \
    timing.cpp \
    NoteEditeur.cpp \
    FenetrePrincipale.cpp
