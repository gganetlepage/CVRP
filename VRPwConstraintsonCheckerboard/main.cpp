#include "lecturetxt.h"
#include "plateau.h"
#include "robot.h"
#include "client.h"
#include "obstacle.h"
#include "probleme.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <typeinfo>

using namespace std;

int main()
{

    string FichierALire("RobotEnvironnement2.txt"); //C:/Personnel/Programmation/Qt/ProjetRobot2/RobotEnvironnement1.txt
    string FichierEcriture("Solution.txt");//C:/Personnel/Programmation/Qt/ProjetRobot2/Solution1.txt
    ofstream fluxEcriture(FichierEcriture);
    ifstream fluxDeLecture(FichierALire);


    if(fluxDeLecture)
    {
        if(fluxEcriture){
          //lecture plateau
        string ligne;
        getline(fluxDeLecture,ligne); //on saute la 1ere ligne qui est un commentaire
        int pTailleX(0),pTailleY(0);
        fluxDeLecture >> pTailleX >> pTailleY;
        fluxDeLecture.ignore();
        Plateau plateauDeJeu(pTailleX, pTailleY);



        //lecture robot
        getline(fluxDeLecture,ligne);
       int rPositionX(0),rPositionY(0),capacite(0);
       fluxDeLecture >> rPositionX >> rPositionY >> capacite;
       fluxDeLecture.ignore();
       Robot robot(rPositionX,rPositionY,capacite);

       //lecture clients
       getline(fluxDeLecture,ligne);
       int nbClients(0);
       fluxDeLecture >> nbClients;
       vector<Client> listeClients;
       int cPositionX(0), cPositionY(0), cDemande(0);
       for (int i(0);i<nbClients;i++) {
           fluxDeLecture >> cPositionX >> cPositionY >> cDemande;
           listeClients.push_back(Client(cPositionX, cPositionY, cDemande));
       }
       fluxDeLecture.ignore();

       //lecture obstacles
       getline(fluxDeLecture,ligne);
       int nbObstacles(0);
       fluxDeLecture >> nbObstacles;
       vector<Obstacle> listeObstacles;
       int oPositionX(0),oPositionY(0),oTailleX(0),oTailleY(0);
       for (int i(0);i<nbObstacles;i++) {
           fluxDeLecture >> oPositionX >> oPositionY >> oTailleX >> oTailleY;
           listeObstacles.push_back(Obstacle(oPositionX,oPositionY,oTailleX,oTailleY));
       }
       fluxDeLecture.ignore();

       cout<< "ENONCE"<<endl;
       fluxEcriture<< "Enonce"<<endl;

       //affichage terrain
       cout << "plateau"<<endl;
       fluxEcriture << "plateau"<<endl;
       plateauDeJeu.showTaille();
       plateauDeJeu.ecriturePlateau(fluxEcriture);

       //affichage du robot, conformite au fichier txt
       cout <<"robot : positionX, position Y, Capacite"<<endl;
       cout << robot.getPositionX() <<" "<<robot.getPositionY()<<" "<<robot.getCapacite()<<endl;
       fluxEcriture <<"robot : positionX, position Y, Capacite"<<endl;
       robot.ecritureRobot(fluxEcriture);


       //affichage des clients, conformite au fichier txt
       cout << "liste Clients : positionX, positionY, demande "<< endl;
       fluxEcriture << "liste Clients : positionX, positionY, demande "<< endl;

       for (int i(0);i<listeClients.size();i++) {
           listeClients[i].showClient();
           listeClients[i].ecritureClient(fluxEcriture);
       }
       //affichage des obstacles, conformite au fichier txt
       cout << "liste Obstacles : positionX, positionY, tailleX, tailleY"<< endl;
       fluxEcriture << "liste Obstacles : positionX, positionY, tailleX, tailleY"<< endl;

       for (int i(0);i<listeObstacles.size();i++) {
           listeObstacles[i].showObstacle();
           listeObstacles[i].ecritureObstable(fluxEcriture);
       }

       //Resolution du Probleme

       plateauDeJeu.terrainVierge();
       plateauDeJeu.distanceVierge();
       Probleme probleme(robot,plateauDeJeu,listeClients,listeObstacles);
       probleme.initialisationDistanceElements();

       pair<int,int> position;
       position.first =listeClients[0].getPositionX();
       position.second=listeClients[0].getPositionY();

       //modelisation probleme
       probleme.modelisationTotale();
       //dijkstra
       probleme.dijkstra();
       //glouton
       probleme.algorithmeGlouton();
       cout <<endl<< "SOLUTION"<<endl;
       cout << "Affichage du probleme" << endl;
       fluxEcriture << "SOLUTION" << endl<< "Affichage du probleme"<<endl;
       probleme.showModelisation();
       probleme.ecritureModelisation(fluxEcriture);

       cout << "Algorithme Dijkstra "<<endl<< "Distance entre les differents elements"<<endl;
       fluxEcriture<< "Algorithme Dijkstra "<<endl<< "Distance entre les differents elements"<<endl;
      probleme.showDistance();
      probleme.ecritureDistance(fluxEcriture);
      cout << "Algorithme Glouton proche en proche"<<endl;
      fluxEcriture<< "Algorithme Glouton proche en proche"<<endl;
      probleme.showTournee();
      probleme.ecritureTournee(fluxEcriture);
      probleme.showDistTotale();
      probleme.ecritureDistTotale(fluxEcriture);

      cout << "Informations copiees sur le Fichier Solution.txt"<<endl;



        }
        else {
            cout << "ERREUR : Le fichier d'ecriture n'a pas pu s'ouvrir";
        }
    }
    else
    {
        cout << "ERREUR : Le fichier de lecture n'a pas pu etre lu" << endl;
    }





    return 0;
}




