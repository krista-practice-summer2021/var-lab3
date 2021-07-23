#ifndef PLANET_H
#define PLANET_H

#include <iostream>
using namespace std;

/*
 * @brief The Planet class Планета.
 */
class Planet
{
private:
    int id; //идентификатор
    int population; //население
    int ownerTeam; //идентификатор игрока
    int reproduction; //прибавление за ход
public:
    Planet();
    ~Planet();
    int getId() const;
    void setId(int value);
    int getPopulation() const;
    void setPopulation(int value);
    int getOwnerTeam() const;
    void setOwnerTeam(int value);
    int getReproduction() const;
    void setReproduction(int value);
    void print();
};

#endif // PLANET_H
