#include "movinggroup.h"

int MovingGroup::getFrom() const
{
    return from;
}

void MovingGroup::setFrom(int value)
{
    from = value;
}

int MovingGroup::getTo() const
{
    return to;
}

void MovingGroup::setTo(int value)
{
    to = value;
}

int MovingGroup::getCount() const
{
    return count;
}

void MovingGroup::setCount(int value)
{
    count = value;
}

int MovingGroup::getStepsLeft() const
{
    return stepsLeft;
}

void MovingGroup::setStepsLeft(int value)
{
    stepsLeft = value;
}

int MovingGroup::getOwnerTeam() const
{
    return ownerTeam;
}

void MovingGroup::setOwnerTeam(int value)
{
    ownerTeam = value;
}

void MovingGroup::debugPrint()
{
    cout << getOwnerTeam() << " " << getFrom() << " " << getTo() << " " << getCount() << " " << getStepsLeft() << endl;
}

void MovingGroup::print()
{
    cout << getFrom() << " " << getTo() << " " << getCount() << endl;
}

MovingGroup::MovingGroup()
{

}

MovingGroup::~MovingGroup()
{

}
