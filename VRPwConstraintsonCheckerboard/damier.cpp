#include "damier.h"

#include "robot.h"
#include "plateau.h"
#include "client.h"
#include "obstacle.h"
#include <string>
#include <vector>

Damier::Damier(Robot robot, Plateau plateau, vector<Client> listeClients, vector<Obstacle> listeObstacles):
    m_robot(robot),m_plateau(plateau),m_listeClients(listeClients),m_listeObstacles(listeObstacles)
{
}

//return un tableau indiquant la distance entre une case[x,y] et les clients + base
// en se servant de l'algo de dijkstra


//void Damier::dijkstra()
//{
//    terrain praticable, bool[][] true si case praticable, false sinon

//    tabNoeud[a][b] = distance entre a et b, (inclus la base du robot et tous les clients)
//      info : tabNoeud[a][a] =0 pour tous a
//
//     POUR TOUS client et base du robot : i

//               int distance[][] = distance( entre i et client ou base)

//               distance[Xi][Yi] = 0

//              gestion des points à traiter : COPIE de terrain praticable

//              TANT QUE il reste des points à traiter:

//                          u = calcul de la case restant à traiter avec la distance mini u=(x,y)

//                          u n'est plus à traiter

//                          POUR TOUT points successeurs (haut, bas, gauche, droite && ne sortant pas du plateau)

//                                      SI dist[Xi][Yi] > dist[Xu][Yu] + 1 (pas sûr)

//                                                  ALORS dist[Xi][Yi] = dist[Xu][Yu] + 1

//              (FIN DU TANT QUE)
//              associer distance entre clients(et base) dans tabNoeud
//              POUR chaque

//

//}








