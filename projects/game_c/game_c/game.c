/*
 ============================================================================
 Name        : samplegame.c
 Author      : Krista, LLC
 Version     : 1.0
 Copyright   : Krista, LLC
 Description : SampleGame
 ============================================================================
 */
#pragma warning(disable : 4996)

#include <stdio.h>
#include <stdlib.h>

#define INPUT_MAX_SIZE 1024 //Максимальный размер входных данных
#define INPUT_TEAM_ID_INDEX 0 //Индекс игрока
#define INPUT_MAX_STEPS_INDEX 1 //Индекс максимального количества шагов
#define INPUT_CURRENT_STEP_INDEX 2 //Индекс текущего шага
#define INPUT_PLANET_COUNT_INDEX 3 //Индекс количества планет
#define INPUT_PLANETS_START_INDEX 4 //Индекс первой планеты
#define INPUT_PLANETS_COLUMN_COUNT 4 //Количество колонок в таблице планет
#define INPUT_MOVING_GROUPS_COLUMN_COUNT 5 //Количество колонок в таблице перемещающихся групп
#define INPUT_MAX_PLANETS_COUNT 10 //Максимальное количество планет
#define MAX_MOVING_GROUPS_COUNT 200 //Максимальное количество перемещающихся групп
#define TEAM_ID_COLUMN 1 //Колонка с ID игрока в таблице планет
#define NO_MANS_TEAM_ID -1 // Значение признака не занятой ни одним игроком планеты
#define MG_TEAM_ID_COLUMN_INDEX 0 //Таблица перемещающихся групп: идентификатор игрока
#define MG_PLANET_FROM_COLUMN_INDEX 1 //Таблица перемещающихся групп: планета с
#define MG_PLANET_TO_COLUMN_INDEX 2 //Таблица перемещающихся групп: планета на
#define MG_COUNT_COLUMN_INDEX 3 //Таблица перемещающихся групп: количество поселенцев
#define MG_STEPS_LEFT_COLUMN_INDEX 4 //Таблица перемещающихся групп: осталось лететь

 /*
  * @brief The Planet struct Планета.
  */
struct Planet {
	int planetId; //Идентификатор планеты
	int teamId; //Идентификатор игрока
	int population; //Население
	int reproduction; //Прибавление за ход
};

/*
 * @brief The MovingGroup struct Перемещающаяся группа.
 */
struct MovingGroup {
	int teamId; //Идентификатор игрока
	int from; //Идентификатор планеты с
	int to; //Идентификатор планеты на
	int count; //Количество поселенцев
	int stepsLeft;
};

/*
 * @brief The Round struct Входные данные.
 */
struct Round {
	int teamId; //Идентификатор игрока
	int maxSteps; //Максимальное количество ходов
	int currentStep; //Текущий шаг
	int planetCount; //Количество планет
	int distMapSizeIndex; //Индекс размера таблицы расстояний
	int movingGroupsCountIndex; //Индекс количества перемещающихся групп
	int movingGroupsCount; //Количество перемещающихся групп
	struct Planet planets[INPUT_MAX_PLANETS_COUNT]; //Таблица планет: строка - планета
	int distMap[INPUT_MAX_PLANETS_COUNT][INPUT_MAX_PLANETS_COUNT]; //таблица расстояний: строка расстояние до планет от текущей
	struct MovingGroup movingGroups[MAX_MOVING_GROUPS_COUNT]; //Перемещающиеся группы

	struct Planet ownPlanets[INPUT_MAX_PLANETS_COUNT]; //Планеты игрока
	int ownPlanetsCount; //Количество планет игрока
	struct Planet adversarysPlanets[INPUT_MAX_PLANETS_COUNT]; //Планеты противника
	int adversarysPlanetsCount; //Количество планет противника
	struct Planet noMansPlanets[INPUT_MAX_PLANETS_COUNT]; //Не занятые планеты
	int noMansPlanetsCount; //Количество не занятых планет

	struct MovingGroup ownGroups[MAX_MOVING_GROUPS_COUNT]; //Перемещающиеся группы игрока
	int ownGroupsCount; //Количество перемещающихся групп игрока
	struct MovingGroup adversarysGroups[MAX_MOVING_GROUPS_COUNT]; //Перемещающиеся группы противника
	int adversarysGroupsCount; //Количество перемещающихся групп противника

	struct MovingGroup move[MAX_MOVING_GROUPS_COUNT]; //Выходной массив групп
	int moveCount; //Количество элементов в массиве
	int required; //Количество поселенцев
};

/*
 * Получить Идентификатор противника по идентификатору игрока.
 */
int getAdversaryTeamId(int teamId) {
	return teamId == 1 ? 0 : 1;
}

/*
 * @brief printPlanet Отладочная печать планеты.
 * @param planet планета
 */
void printPlanet(struct Planet planet) {
	printf("%d ", planet.planetId);
	printf("%d ", planet.teamId);
	printf("%d ", planet.population);
	printf("%d\n", planet.reproduction);
}

/*
 * @brief printMovingGroup Отладочная печать группы.
 * @param group группа
 */
void printMovingGroup(struct MovingGroup group) {
	printf("%d ", group.teamId);
	printf("%d ", group.from);
	printf("%d ", group.to);
	printf("%d ", group.count);
	printf("%d\n", group.stepsLeft);
}

/*
 * Отправить выходные данные
 */
void printMovingGroups(struct MovingGroup groups[], int size) {
	printf("%d", size);
	for (int i = 0; i < size; i++) {
		printf("\n");
		printf("%d", groups[i].from);
		printf(" ");
		printf("%d", groups[i].to);
		printf(" ");
		printf("%d", groups[i].count);
	}
}

/*
 * @brief distributePlanets Распределить планеты.
 * @param teamId идентификатор игрока
 * @param planets pointer к массиву планет
 * @param planetsCount количество планет
 * @param ownPlanets pointer к массиву планет игрока
 * @param ownPlanetsCount pointer к количеству планет игрока
 * @param adversarysPlanets pointer к массиву планет противника
 * @param adversarysPlanetsCount pointer к количеству планет противника
 * @param noMansPlanets pointer к массиву незанятых планет
 * @param noMansPlanetsCount pointer к количеству незанятых планет
 */
void distributePlanets(int teamId,
	struct Planet *planets, int planetsCount,
	struct Planet *ownPlanets, int *ownPlanetsCount,
	struct Planet *adversarysPlanets, int *adversarysPlanetsCount,
	struct Planet *noMansPlanets, int *noMansPlanetsCount) {
	int adversarysTeamId = getAdversaryTeamId(teamId);
	for (int i = 0; i < planetsCount; i++) {
		if (planets[i].teamId == teamId) {
			ownPlanets[*ownPlanetsCount] = planets[i];
			*ownPlanetsCount = *ownPlanetsCount + 1;
		}
		if (planets[i].teamId == adversarysTeamId) {
			adversarysPlanets[*adversarysPlanetsCount] = planets[i];
			*adversarysPlanetsCount = *adversarysPlanetsCount + 1;
		}
		if (planets[i].teamId == NO_MANS_TEAM_ID) {
			noMansPlanets[*noMansPlanetsCount] = planets[i];
			*noMansPlanetsCount = *noMansPlanetsCount + 1;
		}
	}
}

/*
 * @brief distributeMovingGroups Распределить перемещающися группы.
 * @param teamId идентификатор игрока
 * @param movingGroups pointer к массиву групп
 * @param movingGroupsCount количество групп
 * @param ownGroups pointer к массиву групп игрока
 * @param ownGroupsCount pointer к количеству групп игрока
 * @param adversarysGroups pointer к массиву групп противника
 * @param adversarysGroupsCount pointer к количеству групп противника
 */
void distributeMovingGroups(int teamId,
	struct MovingGroup *movingGroups, int movingGroupsCount,
	struct MovingGroup *ownGroups, int *ownGroupsCount,
	struct MovingGroup *adversarysGroups, int *adversarysGroupsCount) {
	int adversarysTeamId = getAdversaryTeamId(teamId);
	for (int i = 0; i < movingGroupsCount; i++) {
		if (movingGroups[i].teamId == teamId) {
			ownGroups[*ownGroupsCount] = movingGroups[i];
			*ownGroupsCount = *ownGroupsCount + 1;
		}
		if (movingGroups[i].teamId == adversarysTeamId) {
			adversarysGroups[*adversarysGroupsCount] = movingGroups[i];
			*adversarysGroupsCount = *adversarysGroupsCount + 1;
		}
	}
}

/*
 * Получить входные данные
 * @return указатель на входные данные
 */
struct Round *getRound() {
	struct Round *round = malloc(sizeof(struct Round) + sizeof(int) * INPUT_MAX_SIZE);
	int input[INPUT_MAX_SIZE];
	int i = 0; // counter
	int temp;
	while (scanf("%d", &temp) != EOF && i < INPUT_MAX_SIZE) {
		input[i] = temp;
		i++;
	}
	round->teamId = input[INPUT_TEAM_ID_INDEX];
	round->maxSteps = input[INPUT_MAX_STEPS_INDEX];
	round->currentStep = input[INPUT_CURRENT_STEP_INDEX];
	round->planetCount = input[INPUT_PLANET_COUNT_INDEX];
	round->distMapSizeIndex = round->planetCount * INPUT_PLANETS_COLUMN_COUNT + INPUT_PLANETS_START_INDEX;
	round->movingGroupsCountIndex = round->distMapSizeIndex + 1 + round->planetCount * round->planetCount;
	round->movingGroupsCount = input[round->movingGroupsCountIndex];

	for (int i = INPUT_PLANETS_START_INDEX; i < round->distMapSizeIndex; ) {
		for (int j = 0; j < round->planetCount; j++) {
			round->planets[j].planetId = input[i];
			round->planets[j].teamId = input[i + 1];
			round->planets[j].population = input[i + 2];
			round->planets[j].reproduction = input[i + 3];
			i += INPUT_PLANETS_COLUMN_COUNT;
		}
	}
	for (int i = round->distMapSizeIndex + 1; i < round->movingGroupsCountIndex; ) {
		for (int j = 0; j < round->planetCount; j++) {
			for (int k = 0; k < round->planetCount; k++) {
				round->distMap[j][k] = input[i];
				i++;
			}
		}
	}
	for (int i = round->movingGroupsCountIndex + 1; i < round->movingGroupsCountIndex + 1 + round->movingGroupsCount * INPUT_MOVING_GROUPS_COLUMN_COUNT; ) {
		for (int j = 0; j < round->movingGroupsCount; j++) {
			round->movingGroups[j].teamId = input[i];
			round->movingGroups[j].from = input[i + 1];
			round->movingGroups[j].to = input[i + 2];
			round->movingGroups[j].count = input[i + 3];
			round->movingGroups[j].stepsLeft = input[i + 4];
			i += INPUT_MOVING_GROUPS_COLUMN_COUNT;
		}
	}
	round->ownPlanetsCount = 0;
	round->adversarysPlanetsCount = 0;
	round->noMansPlanetsCount = 0;
	round->ownGroupsCount = 0;
	round->adversarysGroupsCount = 0;
	round->moveCount = 0;
	round->required = 0;

	distributePlanets(round->teamId, round->planets, round->planetCount, round->ownPlanets, &round->ownPlanetsCount, round->adversarysPlanets, &round->adversarysPlanetsCount, round->noMansPlanets, &round->noMansPlanetsCount);
	distributeMovingGroups(round->teamId, round->movingGroups, round->movingGroupsCount, round->ownGroups, &round->ownGroupsCount, round->adversarysGroups, &round->adversarysGroupsCount);
	return round;
}

void makeAMove(struct Round *round) {

	// Место для Вашего кода.

	printMovingGroups(round->move, round->moveCount);
}

int main(void) {

	struct Round *round = getRound();
	makeAMove(round);

	return EXIT_SUCCESS;
}
