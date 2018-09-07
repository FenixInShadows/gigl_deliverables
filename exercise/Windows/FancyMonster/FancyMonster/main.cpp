#include "fancy_monster.generated.h"

#include <iostream>

using namespace std;

int main()
{
	int seed;
	FancyMonster* monster;

	cout << "input seed: ";
	cin >> seed;
	cout << endl;
	RandInit(seed);

	int level;
	do
	{
		cout << "input monster level: 0 ~ 9; input a negative number to terminate" << endl;
		cin >> level;
		if (level >= 0 && level <= 9)
		{
			monster = GenerateFancyMonster(level);
			cout << monster->Print() << endl << endl;
			delete monster;
		}
	} while (level >= 0);

	return 0;
}