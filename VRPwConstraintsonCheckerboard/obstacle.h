#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <fstream>

class Obstacle
{
public:
    Obstacle(int positionX, int positionY, int tailleX, int tailleY);
    void showObstacle() const;
    void ecritureObstable(std::ofstream &monFlux) const;

    int getPositionX() const;
    int getPositionY() const;
    int getTailleX() const;
    int getTailleY() const;

    bool* plateauAvecObstacle(bool plateau[]);

protected:
    int m_positionX;
    int m_positionY;
    int m_tailleX;
    int m_tailleY;


};

#endif // OBSTACLE_H
