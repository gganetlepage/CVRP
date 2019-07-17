#include "lecturetxt.h"
#include <fstream>
#include <string>
#include <iostream>
#include "plateau.h"
#include <string>
#include <fstream>

using namespace std;

//this class reads .txt file and create objects from different classes
//abstract class, no LectureText object, static methods

LectureTxt::LectureTxt()
{
}



Plateau LectureTxt::readPlateauDeJeu(ifstream& fluxDeLecture)
{
    string ligne;
    getline(fluxDeLecture,ligne); //on saute la 1ere ligne qui est un commentaire
    int largeur,longueur;
    fluxDeLecture >> largeur >> longueur;
    fluxDeLecture.ignore();


    Plateau plateauDeJeu(largeur, longueur);
    return plateauDeJeu;
}




void LectureTxt::lecture(string fichierALire)
{
    ifstream fluxDeLecture(fichierALire);
    if(fluxDeLecture)
    {

        //Plateau plateauDeJeu = readPlateauDeJeu(fluxDeLecture);

    }
    else
    {
        cout << "Le fichier n'a pas pu etre lu" << endl;
    }
}

