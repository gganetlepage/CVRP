#ifndef LECTURETXT_H
#define LECTURETXT_H

#include <string>
#include <fstream>
#include "plateau.h"
#include <iosfwd>

using namespace std;

class LectureTxt
{
public:
    LectureTxt();

    static void lecture(string fichierALire);


    static Plateau readPlateauDeJeu(ifstream& fluxDeLecture);

};

#endif // LECTURETXT_H
