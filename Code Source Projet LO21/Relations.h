#ifndef Relations_hpp
#define Relations_hpp

#include <stdio.h>
#include "timing.h"
#include "PluriNotes.h"
#include <string>
#include <typeinfo>

using namespace TIME;


class Couple {
private:
    std::string label;
    Note* Note1;
    Note* Note2;
    
public:
    std::string getLabel() const {return label;}
    Note* getNote1() const {return Note1;}
    Note* getNote2() const {return Note2;}
    void setLabel(const std::string& s){label=s;}
    void setNotes1(Note* N){Note1=N;}
    void setNotes2(Note* N){Note2=N;}
    Couple(Note* A, Note* B, std::string l):Note1(A),Note2(B),label(l){};
};


class Relation{
private:
    std::string titre;
    std::string description;
    bool orientation;
    Couple* couples;
    int nbCouples;
    int nbMaxCouples;
    
public:
    bool getOrientation() const {return orientation;}
    void setOrientation(bool b){orientation=b;}
    void addCouple(Couple& c);
    Relation(const std::string& t, const std::string& d, bool o);
    ~Relation();
};

class Reference: public Relation {

public:
    Reference(const std::string& t, const std::string& d):Relation(t,d, true){};
    ~Reference();
};





#endif /* Relations_h */
