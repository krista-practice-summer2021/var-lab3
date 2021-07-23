#ifndef MOVINGGROUP_H
#define MOVINGGROUP_H

#include <iostream>

using namespace std;

/*
 * @brief The MovingGroup class Перемещающаяся группа.
 */
class MovingGroup
{
private:
    int from; //с
    int to; //на
    int count; //количество
    int stepsLeft; //осталось ходов
    int ownerTeam; //Идентификатор игрока
public:
    MovingGroup();
    ~MovingGroup();
    int getFrom() const;
    void setFrom(int value);
    int getTo() const;
    void setTo(int value);
    int getCount() const;
    void setCount(int value);
    int getStepsLeft() const;
    void setStepsLeft(int value);
    int getOwnerTeam() const;
    void setOwnerTeam(int value);
    void debugPrint();//Отладочная печать
    void print();
};

#endif // MOVINGGROUP_H
