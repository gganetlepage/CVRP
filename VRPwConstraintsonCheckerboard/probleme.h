#ifndef PROBLEME_H
#define PROBLEME_H

#include "robot.h"
#include "plateau.h"
#include "client.h"
#include "obstacle.h"

#include <string>
#include <vector>
#include <iostream>

class Probleme
{
public:
    Probleme(Robot robot, Plateau plateau, vector<Client> listeClients, vector<Obstacle> listeObstacles);


    //calcul des distances entre les éléments du plateau
    void dijkstra();

    //Calcul de l'ordre des tournées via algorithme Glouton proche en proche
    void algorithmeGlouton();

    //initialisation de certains pointeurs
    void initialisationDistanceElements();
    void initialisationClientServi();

    void associationDistRobot();
    void associationDistClient(int i);


    bool clientRestant();
    pair<bool,int> clientRestantCompatible(int capacite, int elementactuel);



    //affichage des informations sur la console
    void showDistance()const;
    void showDistTotale()const;
    void showTournee()const;
    void showModelisation()const;

    //ecriture des informations sur le fichier
    void ecritureDistance(ofstream &fluxEcriture)const;
    void ecritureDistTotale(ofstream &fluxEcriture)const;
    void ecritureTournee(ofstream &fluxEcriture)const;
    void ecritureModelisation(ofstream &fluxEcriture)const;

    //méthodes utilisées pour la modélisation du problème
    void modelisationPlateau();
    void modelisationClient();
    void modelisationRobot();
    void modelisationObstable(Obstacle obstacle);
    void modelisationTousObstacles();
    void modelisationTotale();





protected:

    Robot m_robot;
    Plateau m_plateau;
    std::vector<Client> m_listeClients;
    std::vector<Obstacle> m_listeObstacles;

    int** m_distanceElements;
    bool* m_clientServi;    
    int m_distTotale;
    vector<int> m_tournee;
    char** m_modelisationProbleme;

};

#endif // PROBLEME_H
