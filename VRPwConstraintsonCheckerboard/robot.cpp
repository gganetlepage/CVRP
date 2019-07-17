#include "robot.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

Robot::Robot(int positionX, int positionY, int capacite):
    m_positionX(positionX), m_positionY(positionY),m_capacite(capacite)
{}

void Robot::showRobot() const
{
    cout << m_positionX << " " << m_positionY << " " << m_capacite << endl;
}

void Robot::ecritureRobot(ofstream& monflux) const{
    monflux << m_positionX << " " << m_positionY << " " << m_capacite << endl;
}

int Robot::getPositionX() const
{
     return m_positionX;
}

int Robot::getPositionY() const
{
     return m_positionY;
}

int Robot::getCapacite() const
{
     return m_capacite;
}
