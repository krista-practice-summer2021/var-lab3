#include "round.h"

int Round::getTeamId() const
{
    return teamId;
}

void Round::setTeamId(int value)
{
    teamId = value;
}

int Round::getMaxSteps() const
{
    return maxSteps;
}

void Round::setMaxSteps(int value)
{
    maxSteps = value;
}

int Round::getCurrentStep() const
{
    return currentStep;
}

void Round::setCurrentStep(int value)
{
    currentStep = value;
}

int Round::getPlanetCount() const
{
    return planetCount;
}

void Round::setPlanetCount(int value)
{
    planetCount = value;
}

std::list<Planet> Round::getPlanets() const
{
    return planets;
}

void Round::setPlanets(const std::list<Planet> &value)
{
    planets = value;
}

int Round::getDistanceMapSizeIndex() const
{
    return distanceMapSizeIndex;
}

void Round::setDistanceMapSizeIndex(int value)
{
    distanceMapSizeIndex = value;
}

vector<vector<int> > Round::getDistanceMap() const
{
    return distanceMap;
}

void Round::setDistanceMap(const vector<vector<int> > &value)
{
    distanceMap = value;
}

int Round::getMovingGroupsCountIndex() const
{
    return movingGroupsCountIndex;
}

void Round::setMovingGroupsCountIndex(int value)
{
    movingGroupsCountIndex = value;
}

int Round::getMovingGroupsCount() const
{
    return movingGroupsCount;
}

void Round::setMovingGroupsCount(int value)
{
    movingGroupsCount = value;
}

std::list<MovingGroup> Round::getMovingGroups() const
{
    return movingGroups;
}

void Round::setMovingGroups(const std::list<MovingGroup> &value)
{
    movingGroups = value;
}

void Round::makeAMove()
{
	// Место для Вашего кода.
    cout << move.size() << endl;
    for(MovingGroup g : move){
        g.print();
    }
}

void Round::debugPrint()
{
    cout << "Team id " << teamId << endl;
    cout << "Max steps " << maxSteps << endl;
    cout << "Current step " << currentStep << endl;
    cout << "Planet count " << planetCount << endl;
    cout << "Planets:" << endl;
    for(Planet p : planets){
        p.print();
    }
    cout << "Dist Map size " << planetCount << endl;
    for(int i = 0; i < planetCount; i++){
        for(int j = 0; j < planetCount; j++){
            //cout << row.at(j) << " ";
            cout << distanceMap[i][j] << " ";
        }
        cout << endl;
    }
    cout << "Moving groups count " << movingGroupsCount << endl;
    for(MovingGroup group : movingGroups){
        group.debugPrint();
    }
    cout << "Own planets count " << ownPlanets.size() << endl;
    for(Planet p : ownPlanets){
        p.print();
    }
    cout << "Adversary planets count " << adversarysPlanets.size() << endl;
    for(Planet p : adversarysPlanets){
        p.print();
    }
    cout << "No man's planets count " << noMansPlanets.size() << endl;
    for(Planet p : noMansPlanets){
        p.print();
    }
    cout << "Own moving groups count " << ownGroups.size() << endl;
    for(MovingGroup g : ownGroups){
        g.debugPrint();
    }
    cout << "Adversary's moving groups count " << adversarysGroups.size() << endl;
    for(MovingGroup g : adversarysGroups){
        g.debugPrint();
    }
}

list<Planet> Round::getOwnPlanets() const
{
    return ownPlanets;
}

void Round::setOwnPlanets(const list<Planet> &value)
{
    ownPlanets = value;
}

list<Planet> Round::getAdversarysPlanets() const
{
    return adversarysPlanets;
}

void Round::setAdversarysPlanets(const list<Planet> &value)
{
    adversarysPlanets = value;
}

list<Planet> Round::getNoMansPlanets() const
{
    return noMansPlanets;
}

void Round::setNoMansPlanets(const list<Planet> &value)
{
    noMansPlanets = value;
}

list<MovingGroup> Round::getOwnGroups() const
{
    return ownGroups;
}

void Round::setOwnGroups(const list<MovingGroup> &value)
{
    ownGroups = value;
}

list<MovingGroup> Round::getAdversarysGroups() const
{
    return adversarysGroups;
}

void Round::setAdversarysGroups(const list<MovingGroup> &value)
{
    adversarysGroups = value;
}

int Round::getAdversaryTeamId()
{
    return teamId == 1 ? 0 : 1;
}

list<MovingGroup> Round::getMove() const
{
    return move;
}

void Round::setMove(const list<MovingGroup> &value)
{
    move = value;
}

Round::Round(std::vector<int> input)
{
    teamId = input.at(Utils::INPUT_TEAM_ID_INDEX);
    maxSteps = input.at(Utils::INPUT_MAX_STEPS_INDEX);
    currentStep = input.at(Utils::INPUT_CURRENT_STEP_INDEX);
    planetCount = input.at(Utils::INPUT_PLANET_COUNT_INDEX);
    distanceMapSizeIndex = planetCount * Utils::INPUT_PLANETS_COLUMN_COUNT + Utils::INPUT_PLANETS_START_INDEX;
    movingGroupsCountIndex = distanceMapSizeIndex + planetCount * planetCount + 1;
    movingGroupsCount = input.at(movingGroupsCountIndex);
    for(int i = Utils::INPUT_PLANETS_START_INDEX; i < distanceMapSizeIndex; ){
        Planet planet = Planet();
        planet.setId(input.at(i));
        planet.setOwnerTeam(input.at(i + 1));
        planet.setPopulation(input.at(i + 2));
        planet.setReproduction(input.at(i + 3));
        planets.push_back(planet);
        i += Utils::INPUT_PLANETS_COLUMN_COUNT;
    }
    vector<int> row(planetCount);
    for(int i = distanceMapSizeIndex + 1; i < movingGroupsCountIndex; ){
        for(int j = 0; j < planetCount; j++){
            row = vector<int>(planetCount);
            for(int k = 0; k < planetCount; k++){
                row.at(k) = input.at(i);
                i++;
            }
            distanceMap.push_back(row);
        }
    }
    MovingGroup group;
    for(int i = movingGroupsCountIndex + 1; i < movingGroupsCountIndex + 1 + movingGroupsCount * Utils::INPUT_MOVING_GROUPS_COLUMN_COUNT; ){
        group = MovingGroup();
        group.setOwnerTeam(input.at(i));
        group.setFrom(input.at(i + 1));
        group.setTo(input.at(i + 2));
        group.setCount(input.at(i + 3));
        group.setStepsLeft(input.at(i + 4));
        movingGroups.push_back(group);
        i += Utils::INPUT_MOVING_GROUPS_COLUMN_COUNT;
    }

    //Отчёты по планетам
    const int adversaryTeamId = getAdversaryTeamId(); //ID противника
    for(Planet p : planets){
        if(p.getOwnerTeam() == teamId){
            ownPlanets.push_back(p);
        } else if (p.getOwnerTeam() == adversaryTeamId){
            adversarysPlanets.push_back(p);
        } else if (p.getOwnerTeam() == Utils::NO_MANS_TEAM_ID){
            noMansPlanets.push_back(p);
        }
    }
    for(MovingGroup g: movingGroups){
        if(g.getOwnerTeam() == teamId){
            ownGroups.push_back(g);
        } else if(g.getOwnerTeam() == adversaryTeamId){
            adversarysGroups.push_back(g);
        }
    }
}

Round::~Round()
{
    
}
