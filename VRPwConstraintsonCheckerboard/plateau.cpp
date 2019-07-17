#include "plateau.h"
#include "obstacle.h"
#include <string>
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;


Plateau::Plateau(int tailleX, int tailleY):
    m_tailleX(tailleX), m_tailleY(tailleY), m_terrain(nullptr), m_distance(nullptr)
{
}//m_terrain(nullptr)


int Plateau::getTailleX() const
{
    return m_tailleX;
}

int Plateau::getTailleY() const
{
    return m_tailleY;
}

bool** Plateau::getTerrain() const
{
    return m_terrain;
}

int** Plateau::getDistance() const
{
    return m_distance;
}

void Plateau::showTaille() const{
    cout <<  m_tailleX<< " "<< m_tailleY << endl;
}

void Plateau::showTerrain()const{
    cout << "terrain de jeu : " << endl;
    for(int i(0) ; i<m_tailleX; i++){
        for(int j(0); j<m_tailleY;j++){
            cout << m_terrain[i][j] << " ";
            }
        cout << endl;
    }
}

void Plateau::showDistance() const{
    cout << "tableau des distances : " << endl;
    for(int i(0) ; i<m_tailleX; i++){
        for(int j(0); j<m_tailleY;j++){
            cout << m_distance[i][j] << " ";
            }
        cout << endl;
    }
}

void Plateau::ecriturePlateau(ofstream &monFlux) const{
    monFlux <<  m_tailleX<< " "<< m_tailleY << endl;
}

void Plateau::terrainVierge(){

    m_terrain = new bool*[m_tailleX];
    for(int i(0) ; i<m_tailleX; i++){
        m_terrain[i]= new bool[m_tailleY];
        for(int j(0); j<m_tailleY;j++){
            m_terrain[i][j] =true;
            }
    }
}


void Plateau::terrainModifie(Obstacle obstacle)
{
    int x = obstacle.getPositionX();
    int y = obstacle.getPositionY();
    for (int i(0); i<obstacle.getTailleX();i++)
    {
        for (int j(0);j<obstacle.getTailleY();j++)
        {                     
            m_terrain[x+i][y+j]=false;
        }
    }
}

void Plateau::terrainTotalModifie(vector<Obstacle> listeObstacles)
{
    this->terrainVierge();
    int nombre(listeObstacles.size());
    for (int k(0);k<nombre;k++) {
        this->terrainModifie(listeObstacles[k]);
    }
}

void Plateau::caseDeDepart(int x, int y){
    m_distance[x][y]=0;
}

void Plateau::caseConsomme(int x, int y){
    m_terrain[x][y]= false;
}

bool Plateau::resteCaseATraiter(){
    int i(0),j(0), compteur(0);
    while(compteur==0 && i<m_tailleX){
        while (compteur==0 && j<m_tailleY) {
            if(m_terrain[i][j]){
                compteur++;
            }
            j++;
        }
        j=0;
        i++;
    }
    return(compteur!=0);

}

void Plateau::distanceVierge(){
    int max = m_tailleX* m_tailleY;
    m_distance = new int*[m_tailleX];
    for(int i(0) ; i<m_tailleX; i++){
        m_distance[i]= new int[m_tailleY];
        for(int j(0); j<m_tailleY;j++){
            m_distance[i][j] =max;
            }
    }
}

pair<int,int> Plateau::minTab(){ //DANGER : c'est le min des cases non utilisees
    pair<int,int> position;
    position.first = 0;
    position.second = 0;
    int distanceMin = m_tailleX*m_tailleY;
    for (int i(0);i<m_tailleX;i++) {
        for (int j(0);j<m_tailleY;j++) {
            if(m_terrain[i][j] && distanceMin> m_distance[i][j]){
                distanceMin = m_distance[i][j];
                position.first = i;
                position.second = j;
            }

        }
    }
    return position;

}


void Plateau::distanceModifie(pair<int,int> position, int valeur){
    m_distance[position.first][position.second]=valeur;
}


bool Plateau::directionGauche(int x, int y) const{ //Gauche =(x,y-1)
    if(y,x>=0 && x<m_tailleX && y<m_tailleY){
        return(y!=0 && m_terrain[x][y-1]);
    }
    else {
        cout << "x ou y est hors du plateau";
    }
}

bool Plateau::directionDroite(int x, int y) const{ //Droite=(x,y+1)
    if(y,x>=0 && x<m_tailleX && y<m_tailleY){
        return(y!=(m_tailleY-1) && m_terrain[x][y+1]);
    }
    else {
        cout << "x ou y est hors du plateau";
    }
}

bool Plateau::directionHaut(int x, int y) const{ //Haut=(x-1,y)
    if(y,x>=0 && x<m_tailleX && y<m_tailleY){
        return(x!=0 && m_terrain[x-1][y]);
    }
    else {
        cout << "x ou y est hors du plateau";
    }
}

bool Plateau::directionBas(int x, int y) const{ //Bas=(x+1,y)
    if(y,x>=0 && x<m_tailleX && y<m_tailleY){
        return(x!=(m_tailleX-1) && m_terrain[x+1][y]);
    }
    else {
        cout << "x ou y est hors du plateau";
    }
}


void Plateau::successeurHaut(int x, int y){
    if(this->directionHaut(x,y)){
        int comparaison = m_distance[x][y]+1;
        if(m_distance[x-1][y]> comparaison){
            m_distance[x-1][y] = comparaison;
        }
    }
}

void Plateau::successeurBas(int x, int y){
    if(this->directionBas(x,y)){
        int comparaison = m_distance[x][y]+1;
        if(m_distance[x+1][y]> comparaison){
            m_distance[x+1][y] = comparaison;
        }
    }
}

void Plateau::successeurDroite(int x, int y){
    if(this->directionDroite(x,y)){
        int comparaison = m_distance[x][y]+1;
        if(m_distance[x][y+1]> comparaison){
            m_distance[x][y+1] = comparaison;

        }
    }
}

void Plateau::successeurGauche(int x, int y){
    if(this->directionGauche(x,y)){
        int comparaison = m_distance[x][y]+1;
        if(m_distance[x][y-1]> comparaison){
            m_distance[x][y-1] = comparaison;
        }
    }
}

void Plateau::successeurTotal(int x, int y){
    this->successeurBas(x,y);
    this->successeurHaut(x,y);
    this->successeurDroite(x,y);
    this->successeurGauche(x,y);
}

void Plateau::dijkstraCase(int x, int y){
    caseDeDepart(x,y);
    caseConsomme(x,y);
    successeurTotal(x,y);
    pair<int,int> successeur;
    while (resteCaseATraiter()) {
        successeur =this->minTab();
        caseConsomme(successeur.first,successeur.second);
        this->successeurTotal(successeur.first,successeur.second);
        //this->showPlateau();
    }
}

void Plateau::dijkstraCaseComplet(int x, int y,vector<Obstacle> listeObstacles){    
    this->distanceVierge();
    this->terrainTotalModifie(listeObstacles);
    //this->showPlateau();
    this->dijkstraCase(x,y);
}//après execution, m_terrain est un tableau rempli de 0 et
//et m_distance[i][j] correspond à la distance entre la case (x,y) et (i,j) pour les cases praticables


//delete pointeurTerrain
