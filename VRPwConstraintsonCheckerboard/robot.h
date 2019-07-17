#ifndef ROBOT_H
#define ROBOT_H

#include <fstream>

class Robot
{
public:
    Robot(int positionX, int positionY, int capacite);

    void showRobot()const;
    void ecritureRobot( std::ofstream& monflux) const;

    int getPositionX() const;
    int getPositionY() const;
    int getCapacite() const;

protected:

    int m_positionX;
    int m_positionY;
    int m_capacite;
};

#endif // ROBOT_H
