#include "probleme.h"

#include "plateau.h"
#include "robot.h"
#include "client.h"
#include "obstacle.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

Probleme::Probleme(Robot robot, Plateau plateau, vector<Client> listeClients, vector<Obstacle> listeObstacles):
    m_robot(robot),m_plateau(plateau),m_listeClients(listeClients),m_listeObstacles(listeObstacles),m_distTotale(0), m_tournee(0), m_modelisationProbleme(0)
{
}

void Probleme::dijkstra(){
    this->initialisationDistanceElements();
    int nbClients = m_listeClients.size();
    //on s'occupe d'abord des distances par rapport au robot
    m_plateau.dijkstraCaseComplet(m_robot.getPositionX(),m_robot.getPositionY(),m_listeObstacles);
    this->associationDistRobot();

    //on s'occupe maintenant des distances en partant des clients
    for (int i(0);i<nbClients;i++) {
        m_plateau.dijkstraCaseComplet(m_listeClients[i].getPositionX(),m_listeClients[i].getPositionY(),m_listeObstacles);
        this->associationDistClient(i);
    }
}

void Probleme::algorithmeGlouton(){
    this->initialisationClientServi();
    int numClientDeLaTournee, elementActuel, capaReelleRobot;
    pair<bool,int> ClientADistMinACapaReelle;
    m_tournee.push_back(0); //on démarre de la base du robot
    while (clientRestant()) {
        elementActuel = 0; //on initialise le début d'une tournée
        capaReelleRobot = m_robot.getCapacite();
        ClientADistMinACapaReelle = clientRestantCompatible(capaReelleRobot,elementActuel);
        while (ClientADistMinACapaReelle.first) { //Tant que la capacite restante du robot est suffisante
            numClientDeLaTournee = ClientADistMinACapaReelle.second; // on va chez le client compatible le plus proche
            capaReelleRobot -= m_listeClients[numClientDeLaTournee].getDemande();
            m_tournee.push_back(numClientDeLaTournee+1);//on ajoute le numéro d'élément, donc +1 pour les clients
            m_distTotale += m_distanceElements[elementActuel][numClientDeLaTournee+1];
            elementActuel = numClientDeLaTournee+1;
            m_clientServi[numClientDeLaTournee]=true;
            ClientADistMinACapaReelle = clientRestantCompatible(capaReelleRobot,elementActuel);
        }
        m_distTotale += m_distanceElements[elementActuel][0]; //si element actuel = robot, pas de souci car m_distance[0][0] = 0;
        m_tournee.push_back(0); //le robot doit revenir à la base quand il n'a plus assez de capacite
    }
}

void Probleme::initialisationDistanceElements(){
    int taille = m_listeClients.size()+1; // +1 car il faut ajouter le robot en 1ere case
    m_distanceElements = new int* [taille];
    for (int i(0);i<taille;i++) {
        m_distanceElements[i]= new int[taille];
        for (int j(0);j<taille;j++) {
            m_distanceElements[i][j]=0;
        }
    }
}

void Probleme::initialisationClientServi(){
    int taille = m_listeClients.size();
    m_clientServi = new bool[taille];
    for (int i(0);i<taille;i++) {
        m_clientServi[i] = false;

    }
}

void Probleme::associationDistRobot(){ // i correspond à si tu es
    int nbClients = m_listeClients.size();
    int x,y,dist;
    int** distance = m_plateau.getDistance();
    for (int i(0);i<nbClients;i++) {
        x = m_listeClients[i].getPositionX();
        y = m_listeClients[i].getPositionY();
       dist = distance[x][y];
        m_distanceElements[0][i+1]=dist;
        m_distanceElements[i+1][0]=dist;
    }
}

void Probleme::associationDistClient(int i){
    int** distance = m_plateau.getDistance();
    int nbClients = m_listeClients.size();

    int xRobot = m_robot.getPositionX();
    int yRobot = m_robot.getPositionY();
    int distRobot = distance[xRobot][yRobot];
    int x,y,dist;
    m_distanceElements[0][i+1] = distRobot;
    m_distanceElements[i+1][0] = distRobot;
    for(int k(0);k<nbClients;k++){
        if(k!=i){
            x = m_listeClients[k].getPositionX();
            y = m_listeClients[k].getPositionY();
            dist = distance[x][y];
            m_distanceElements[k+1][i+1]=dist;
            m_distanceElements[i+1][k+1]=dist;
        }
    }
}


bool Probleme::clientRestant(){
    int i(0), compteur(0);
    while (compteur==0 & i< m_listeClients.size()) {
        if(!m_clientServi[i]){ //si client n'a pas été servi, compteur++ et sort de la boucle
            compteur++;
        }
        i++;
    }
    return(compteur!=0);
}

pair<bool,int> Probleme::clientRestantCompatible(int capaciteRestanteRobot, int elementactuel){    
    pair<bool,int> clientRestantCompatible;
    bool possible(false);
    int numClient;
    int distMin = INT_MAX;
    int nbClients = m_listeClients.size();
    for (int i(0);i<nbClients;i++) {
//        bool a =(i!=(elementactuel-1));
//        bool b = !m_clientServi[i];
//        bool c = m_listeClients[i].getDemande()<=capaciteRestanteRobot;
//        bool d = m_distanceElements[elementactuel][i+1]<distMin;
//        cout << a <<" ";
//        cout << b<< " " ;
//        cout << c<< " ";
//        cout << d<<endl;
        if((i!=(elementactuel-1))&& !m_clientServi[i]&& m_listeClients[i].getDemande()<=capaciteRestanteRobot && m_distanceElements[elementactuel][i+1]<distMin){
            // on ne veut pas aller sur place + on ne veut pas un client déjà servi + le robot doit avoir la capacite pour prendre la demande + on veut le client le plus proche
            possible = true;
            numClient = i;
            distMin = m_distanceElements[elementactuel][i+1];
        }
    }
    clientRestantCompatible.first = possible;
    clientRestantCompatible.second = numClient;
    return clientRestantCompatible;

}



void Probleme::showDistance()const{
    int taille = m_listeClients.size() +1;
    for (int i = 0; i < taille; ++i) {
        for (int j(0);j<taille;j++) {
            cout << m_distanceElements[i][j]<< " ";
        }
        cout << endl;
    }
}

void Probleme::showDistTotale()const{
    cout << "distance totale de la tournee : "<<m_distTotale<<endl;
}

void Probleme::showTournee()const{
    cout <<"tournee du robot : "<<endl;
    int posX,posY;
    for (int i(0);i<m_tournee.size();i++) {
        if(m_tournee[i]==0){ //cas robot
            cout << m_robot.getPositionX()<<" "<<m_robot.getPositionY()<<endl;
        }
        else {
            cout<< m_listeClients[m_tournee[i]-1].getPositionX()<<" "<<m_listeClients[m_tournee[i]-1].getPositionY()<<endl;
        }
    }
}

void Probleme::showModelisation()const{
    int tailleX = m_plateau.getTailleX();
    int tailleY = m_plateau.getTailleY();
    for (int i(0);i<tailleX;i++) {
        for (int j(0);j<tailleY;j++) {
            cout<< m_modelisationProbleme[i][j] << " ";
        }
        cout << endl;
    }
}

void Probleme::ecritureDistance(ofstream &fluxEcriture)const{
    int taille = m_listeClients.size() +1;
    for (int i = 0; i < taille; ++i) {
        for (int j(0);j<taille;j++) {
            fluxEcriture << m_distanceElements[i][j]<< " ";
        }
        fluxEcriture << endl;
    }
}

void Probleme::ecritureDistTotale(ofstream &fluxEcriture) const{
    fluxEcriture << "distance totale de la tournee : "<< m_distTotale<<endl;
}

void Probleme::ecritureTournee(ofstream &fluxEcriture) const{
    fluxEcriture <<"tournee du robot : "<<endl;
    int posX,posY;
    for (int i(0);i<m_tournee.size();i++) {
        if(m_tournee[i]==0){ //cas robot
            fluxEcriture << m_robot.getPositionX()<<" "<<m_robot.getPositionY()<<endl;
        }
        else {
            fluxEcriture<< m_listeClients[m_tournee[i]-1].getPositionX()<<" "<<m_listeClients[m_tournee[i]-1].getPositionY()<<endl;
        }
    }
}

void Probleme::ecritureModelisation(ofstream &fluxEcriture) const{
    int tailleX = m_plateau.getTailleX();
    int tailleY = m_plateau.getTailleY();
    for (int i(0);i<tailleX;i++) {
        for (int j(0);j<tailleY;j++) {
            fluxEcriture<< m_modelisationProbleme[i][j] << " ";
        }
        fluxEcriture << endl;
    }
}

void  Probleme::modelisationPlateau(){
    int tailleX = m_plateau.getTailleX();
    int tailleY = m_plateau.getTailleY();
    m_modelisationProbleme = new char*[tailleX];
    for (int i(0);i<tailleX;i++) {
        m_modelisationProbleme[i] = new char[tailleY];
        for (int j(0);j<tailleY;j++) {
            m_modelisationProbleme[i][j]= '.';
        }
    }
}

void Probleme::modelisationClient(){
    int nbClients(m_listeClients.size());
    for (int i(0);i<nbClients;i++) {
        m_modelisationProbleme[m_listeClients[i].getPositionX()][m_listeClients[i].getPositionY()]= 'C';
    }
}

void Probleme::modelisationRobot(){
    m_modelisationProbleme[m_robot.getPositionX()][m_robot.getPositionY()]= 'R';
}

void Probleme::modelisationObstable(Obstacle obstacle){
    int x = obstacle.getPositionX();
    int y = obstacle.getPositionY();
    for (int i(0); i<obstacle.getTailleX();i++)
    {
        for (int j(0);j<obstacle.getTailleY();j++)
        {
            m_modelisationProbleme[x+i][y+j]='O';
        }
    }
}

void Probleme::modelisationTousObstacles(){
    int nbObstacles(m_listeObstacles.size());
    for(int i(0); i<nbObstacles;i++){
        this->modelisationObstable(m_listeObstacles[i]);
    }
}

void Probleme::modelisationTotale(){
    this->modelisationPlateau();
    this->modelisationClient();
    this->modelisationRobot();
    this->modelisationTousObstacles();
}


