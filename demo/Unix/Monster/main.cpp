#include "monster.generated.h"

#include <iostream>

using namespace std;

int main()
{
	int seed;
	DungeonMonster* monster_set[10];

	cout << "input seed: ";
	cin >> seed;
	RandInit(seed);
	cout << "Monster stats in Easy Room #" << seed << endl;
	GenerateEasyRoomMonsters(monster_set);
	for (int j = 0; j < 10; j++)
	{
		cout << monster_set[j]->damage << "  ";
		delete monster_set[j];
	}
	cout << endl << endl;

	cout << "input seed: ";
	cin >> seed;
	RandInit(seed);
	cout << "Monster stats in Hard Room #" << seed << endl;
	GenerateHardRoomMonsters(monster_set);
	for (int j = 0; j < 10; j++)
	{
		cout << monster_set[j]->damage << "  ";
		delete monster_set[j];
	}
	cout << endl << endl;

	return 0;
}