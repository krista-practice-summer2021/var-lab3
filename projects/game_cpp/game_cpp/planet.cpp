#include "planet.h"

int Planet::getId() const
{
    return id;
}

void Planet::setId(int value)
{
    id = value;
}

int Planet::getPopulation() const
{
    return population;
}

void Planet::setPopulation(int value)
{
    population = value;
}

int Planet::getOwnerTeam() const
{
    return ownerTeam;
}

void Planet::setOwnerTeam(int value)
{
    ownerTeam = value;
}

int Planet::getReproduction() const
{
    return reproduction;
}

void Planet::setReproduction(int value)
{
    reproduction = value;
}

void Planet::print()
{
    cout << id << " " << ownerTeam << " " << population << " " << reproduction << endl;
}

Planet::Planet()
{

}

Planet::~Planet()
{

}
