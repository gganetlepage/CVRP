#include "obstacle.h"
#include "plateau.h"
#include <iostream>

using namespace std;

Obstacle::Obstacle(int positionX, int positionY, int tailleX, int tailleY):
    m_positionX(positionX),m_positionY(positionY),m_tailleX(tailleX),m_tailleY(tailleY)
{
}

void Obstacle::showObstacle() const //test check function
{
    cout << m_positionX <<" "<<m_positionY<<" "<<m_tailleX<<" "<<m_tailleY<< endl;
}

void Obstacle::ecritureObstable(std::ofstream &monFlux) const{
    monFlux << m_positionX <<" "<<m_positionY<<" "<<m_tailleX<<" "<<m_tailleY<< endl;
}

int Obstacle::getPositionX()const{
    return m_positionX;
}

int Obstacle::getPositionY() const{
    return m_positionY;
}

int Obstacle::getTailleX() const{
    return m_tailleX;
}

int Obstacle::getTailleY() const{
    return m_tailleY;
}





