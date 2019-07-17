#include "client.h"
#include <iostream>
#include <fstream>
using namespace std;

Client::Client(int positionX, int posiitionY, int demande):
    m_positionX(positionX), m_positionY(posiitionY), m_demande(demande)
{
}

void Client::showClient() const
{
    cout << m_positionX <<" "<<m_positionY<<" "<<m_demande<<endl;
}

void Client::ecritureClient(ofstream& monflux) const {
    monflux << m_positionX <<" "<<m_positionY<<" "<<m_demande<<endl;
}

int Client::getPositionX() const
{
    return m_positionX;
}

int Client::getPositionY() const
{
    return m_positionY;
}


int Client::getDemande() const
{
    return m_demande;
}


