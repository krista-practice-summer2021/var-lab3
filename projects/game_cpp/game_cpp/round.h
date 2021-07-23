#ifndef ROUND_H
#define ROUND_H

#include <vector>
#include <list>
#include <iostream>
#include "planet.h"
#include "movinggroup.h"
#include "utils.h"

using namespace std;

/*
 * @brief The Round class Ход игры.
 */
class Round
{
private:
    std::vector<int> input; //входные данные
    int teamId; //идентификатор игрока
    int maxSteps; //максимальное количество ходов
    int currentStep; //Текущий ход
    int planetCount; //Количество планет
    list<Planet> planets; //Планеты
    int distanceMapSizeIndex; //Индекс размера таблицы расстояний (во входных данных)
    vector<vector<int>> distanceMap; //Таблица расстояний
    int movingGroupsCountIndex; //Индекс количества перемещающихся групп (во входных данных)
    int movingGroupsCount; //Количество перемещающихся групп
    list<MovingGroup> movingGroups; //Перемещающиеся группы
    //Отчёты
    list<Planet> ownPlanets; //Планеты игрока
    list<Planet> adversarysPlanets; //Планеты противника
    list<Planet> noMansPlanets; //Не занятые планеты
    list<MovingGroup> ownGroups; //Перемещающиеся группы игрока
    list<MovingGroup> adversarysGroups; //Перемещающиеся группы противника
    int getAdversaryTeamId(); //Получить Идентификатор противника
	list<MovingGroup> move = {};
public:
    Round(std::vector<int> input);
    ~Round();
    int getTeamId() const;
    void setTeamId(int value);
    int getMaxSteps() const;
    void setMaxSteps(int value);
    int getCurrentStep() const;
    void setCurrentStep(int value);
    int getPlanetCount() const;
    void setPlanetCount(int value);
    list<Planet> getPlanets() const;
    void setPlanets(const list<Planet> &value);
    int getDistanceMapSizeIndex() const;
    void setDistanceMapSizeIndex(int value);
    vector<vector<int> > getDistanceMap() const;
    void setDistanceMap(const vector<vector<int> > &value);
    int getMovingGroupsCountIndex() const;
    void setMovingGroupsCountIndex(int value);
    int getMovingGroupsCount() const;
    void setMovingGroupsCount(int value);
    list<MovingGroup> getMovingGroups() const;
    void setMovingGroups(const list<MovingGroup> &value);
    void makeAMove();
    void debugPrint();
    list<Planet> getOwnPlanets() const;
    void setOwnPlanets(const list<Planet> &value);
    list<Planet> getAdversarysPlanets() const;
    void setAdversarysPlanets(const list<Planet> &value);
    list<Planet> getNoMansPlanets() const;
    void setNoMansPlanets(const list<Planet> &value);
    list<MovingGroup> getOwnGroups() const;
    void setOwnGroups(const list<MovingGroup> &value);
    list<MovingGroup> getAdversarysGroups() const;
    void setAdversarysGroups(const list<MovingGroup> &value);
    list<MovingGroup> getMove() const;
    void setMove(const list<MovingGroup> &value);
};

#endif // ROUND_H
