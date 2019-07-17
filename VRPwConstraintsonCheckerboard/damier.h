#ifndef DAMIER_H
#define DAMIER_H

#include "robot.h"
#include "plateau.h"
#include "client.h"
#include "obstacle.h"
#include <string>
#include <vector>



class Damier
{
public:
    Damier(Robot robot, Plateau plateau, vector<Client> listeClients, vector<Obstacle> listeObstacles);




protected:
    Robot m_robot;
    Plateau m_plateau;
    std::vector<Client> m_listeClients;
    std::vector<Obstacle> m_listeObstacles;




};

#endif // DAMIER_H
