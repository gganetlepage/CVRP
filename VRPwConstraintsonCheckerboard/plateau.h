#ifndef PLATEAU_H
#define PLATEAU_H

#include <string>
#include <iostream>
#include <vector>
#include "obstacle.h"
using namespace std;

class Plateau
{
public:
    Plateau(int tailleX, int tailleY);

    int getTailleX() const;
    int getTailleY() const;
    bool** getTerrain() const;
    int** getDistance() const;

    void showTaille() const;
    void showTerrain()const;
    void showDistance()const;
    void ecriturePlateau(std::ofstream &monFlux) const;

    void terrainVierge();
    void terrainModifie(Obstacle obstacle);
    void terrainTotalModifie(vector<Obstacle> listeObstacles);

    void caseDeDepart(int x, int y);
    void caseConsomme(int x, int y);
    bool resteCaseATraiter();

    void distanceVierge();
    pair<int,int> minTab();

    void distanceModifie(pair<int,int> position, int valeur);


    bool directionGauche(int x, int y) const;
    bool directionDroite(int x, int y) const;
    bool directionHaut(int x, int y) const;
    bool directionBas(int x, int y) const;

    void successeurHaut(int x, int y);
    void successeurBas(int x, int y);
    void successeurDroite(int x, int y);
    void successeurGauche(int x, int y);
    void successeurTotal(int x, int y);

    void dijkstraCase(int i, int j);
    void dijkstraCaseComplet(int x, int y,vector<Obstacle> listeObstacles);

protected:
    int m_tailleX;
    int m_tailleY;
    bool** m_terrain;

    int** m_distance;




};

#endif // PLATEAU_H
