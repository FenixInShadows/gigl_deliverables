#include "good_morning.generated.h"

#include <iostream>

using namespace std;

int main()
{
	int seed;
	Greeting* g;

	cout << "input seed: ";
	cin >> seed;
	cout << endl;
	RandInit(seed);

	char ch;
	while (true)
	{
		cout << "input any charactor; input 'q' to terminate" << endl;
		cin >> ch;
		if (ch == 'q')
			break;

		g = GenerateGreeting();
		cout << g->Print() << endl << endl;
		delete g;
	}

	return 0;
}
