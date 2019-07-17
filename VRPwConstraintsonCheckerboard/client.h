#ifndef CLIENT_H
#define CLIENT_H

#include <fstream>


class Client
{
public:
    Client(int positionX, int posiitionY, int demande);

    void showClient() const;
    void ecritureClient(std::ofstream& monflux) const;

    int getPositionX() const;
    int getPositionY() const;
    int getDemande() const;


protected:

    int m_positionX;
    int m_positionY;
    int m_demande;
};

#endif // CLIENT_H
