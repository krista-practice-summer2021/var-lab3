#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <iostream>

using namespace std;

/*
 * @brief The Utils class Вспомогательные методы.
 */
class Utils
{
public:
    const static int INPUT_MAX_SIZE = 1000; //Максимальный размер входных данных
    const static int INPUT_TEAM_ID_INDEX = 0; //Индекс игрока
    const static int INPUT_MAX_STEPS_INDEX = 1; //Индекс максимального количества шагов
    const static int INPUT_CURRENT_STEP_INDEX = 2; //Индекс текущего шага
    const static int INPUT_PLANET_COUNT_INDEX = 3; //Индекс количества планет
    const static int INPUT_PLANETS_START_INDEX = 4; //Индекс первой планеты
    const static int INPUT_PLANETS_COLUMN_COUNT = 4; //Количество колонок в таблице планет
    const static int INPUT_MOVING_GROUPS_COLUMN_COUNT = 5; //Количество колонок в таблице перемещающихся групп
    const static int INPUT_MAX_PLANETS_COUNT = 10; //Максимальное количество планет
    const static int MAX_MOVING_GROUPS_COUNT = 200; //Максимальное количество перемещающихся групп
    const static int TEAM_ID_COLUMN = 1; //Колонка с ID игрока в таблице планет
    const static int NO_MANS_TEAM_ID = -1; // Значение признака не занятой ни одним игроком планеты
    const static int MG_TEAM_ID_COLUMN_INDEX = 0; //Таблица перемещающихся групп: идентификатор игрока
    const static int MG_PLANET_FROM_COLUMN_INDEX = 1; //Таблица перемещающихся групп: планета с
    const static int MG_PLANET_TO_COLUMN_INDEX = 2; //Таблица перемещающихся групп: планета на
    const static int MG_COUNT_COLUMN_INDEX = 3; //Таблица перемещающихся групп: количество поселенцев
    const static int MG_STEPS_LEFT_COLUMN_INDEX = 4; //Таблица перемещающихся групп: осталось лететь
    Utils();
    ~Utils();
    static std::vector<int> readSystemInput(); //Прочитать ввод
};

#endif // UTILS_H
