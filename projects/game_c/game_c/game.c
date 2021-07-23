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

#define INPUT_MAX_SIZE 1024 //������������ ������ ������� ������
#define INPUT_TEAM_ID_INDEX 0 //������ ������
#define INPUT_MAX_STEPS_INDEX 1 //������ ������������� ���������� �����
#define INPUT_CURRENT_STEP_INDEX 2 //������ �������� ����
#define INPUT_PLANET_COUNT_INDEX 3 //������ ���������� ������
#define INPUT_PLANETS_START_INDEX 4 //������ ������ �������
#define INPUT_PLANETS_COLUMN_COUNT 4 //���������� ������� � ������� ������
#define INPUT_MOVING_GROUPS_COLUMN_COUNT 5 //���������� ������� � ������� �������������� �����
#define INPUT_MAX_PLANETS_COUNT 10 //������������ ���������� ������
#define MAX_MOVING_GROUPS_COUNT 200 //������������ ���������� �������������� �����
#define TEAM_ID_COLUMN 1 //������� � ID ������ � ������� ������
#define NO_MANS_TEAM_ID -1 // �������� �������� �� ������� �� ����� ������� �������
#define MG_TEAM_ID_COLUMN_INDEX 0 //������� �������������� �����: ������������� ������
#define MG_PLANET_FROM_COLUMN_INDEX 1 //������� �������������� �����: ������� �
#define MG_PLANET_TO_COLUMN_INDEX 2 //������� �������������� �����: ������� ��
#define MG_COUNT_COLUMN_INDEX 3 //������� �������������� �����: ���������� ����������
#define MG_STEPS_LEFT_COLUMN_INDEX 4 //������� �������������� �����: �������� ������

 /*
  * @brief The Planet struct �������.
  */
struct Planet {
	int planetId; //������������� �������
	int teamId; //������������� ������
	int population; //���������
	int reproduction; //����������� �� ���
};

/*
 * @brief The MovingGroup struct �������������� ������.
 */
struct MovingGroup {
	int teamId; //������������� ������
	int from; //������������� ������� �
	int to; //������������� ������� ��
	int count; //���������� ����������
	int stepsLeft;
};

/*
 * @brief The Round struct ������� ������.
 */
struct Round {
	int teamId; //������������� ������
	int maxSteps; //������������ ���������� �����
	int currentStep; //������� ���
	int planetCount; //���������� ������
	int distMapSizeIndex; //������ ������� ������� ����������
	int movingGroupsCountIndex; //������ ���������� �������������� �����
	int movingGroupsCount; //���������� �������������� �����
	struct Planet planets[INPUT_MAX_PLANETS_COUNT]; //������� ������: ������ - �������
	int distMap[INPUT_MAX_PLANETS_COUNT][INPUT_MAX_PLANETS_COUNT]; //������� ����������: ������ ���������� �� ������ �� �������
	struct MovingGroup movingGroups[MAX_MOVING_GROUPS_COUNT]; //�������������� ������

	struct Planet ownPlanets[INPUT_MAX_PLANETS_COUNT]; //������� ������
	int ownPlanetsCount; //���������� ������ ������
	struct Planet adversarysPlanets[INPUT_MAX_PLANETS_COUNT]; //������� ����������
	int adversarysPlanetsCount; //���������� ������ ����������
	struct Planet noMansPlanets[INPUT_MAX_PLANETS_COUNT]; //�� ������� �������
	int noMansPlanetsCount; //���������� �� ������� ������

	struct MovingGroup ownGroups[MAX_MOVING_GROUPS_COUNT]; //�������������� ������ ������
	int ownGroupsCount; //���������� �������������� ����� ������
	struct MovingGroup adversarysGroups[MAX_MOVING_GROUPS_COUNT]; //�������������� ������ ����������
	int adversarysGroupsCount; //���������� �������������� ����� ����������

	struct MovingGroup move[MAX_MOVING_GROUPS_COUNT]; //�������� ������ �����
	int moveCount; //���������� ��������� � �������
	int required; //���������� ����������
};

/*
 * �������� ������������� ���������� �� �������������� ������.
 */
int getAdversaryTeamId(int teamId) {
	return teamId == 1 ? 0 : 1;
}

/*
 * @brief printPlanet ���������� ������ �������.
 * @param planet �������
 */
void printPlanet(struct Planet planet) {
	printf("%d ", planet.planetId);
	printf("%d ", planet.teamId);
	printf("%d ", planet.population);
	printf("%d\n", planet.reproduction);
}

/*
 * @brief printMovingGroup ���������� ������ ������.
 * @param group ������
 */
void printMovingGroup(struct MovingGroup group) {
	printf("%d ", group.teamId);
	printf("%d ", group.from);
	printf("%d ", group.to);
	printf("%d ", group.count);
	printf("%d\n", group.stepsLeft);
}

/*
 * ��������� �������� ������
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
 * @brief distributePlanets ������������ �������.
 * @param teamId ������������� ������
 * @param planets pointer � ������� ������
 * @param planetsCount ���������� ������
 * @param ownPlanets pointer � ������� ������ ������
 * @param ownPlanetsCount pointer � ���������� ������ ������
 * @param adversarysPlanets pointer � ������� ������ ����������
 * @param adversarysPlanetsCount pointer � ���������� ������ ����������
 * @param noMansPlanets pointer � ������� ��������� ������
 * @param noMansPlanetsCount pointer � ���������� ��������� ������
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
 * @brief distributeMovingGroups ������������ ������������� ������.
 * @param teamId ������������� ������
 * @param movingGroups pointer � ������� �����
 * @param movingGroupsCount ���������� �����
 * @param ownGroups pointer � ������� ����� ������
 * @param ownGroupsCount pointer � ���������� ����� ������
 * @param adversarysGroups pointer � ������� ����� ����������
 * @param adversarysGroupsCount pointer � ���������� ����� ����������
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
 * �������� ������� ������
 * @return ��������� �� ������� ������
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

	// ����� ��� ������ ����.

	printMovingGroups(round->move, round->moveCount);
}

int main(void) {

	struct Round *round = getRound();
	makeAMove(round);

	return EXIT_SUCCESS;
}
