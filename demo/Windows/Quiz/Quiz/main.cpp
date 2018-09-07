#include "quiz.generated.h"

#include <iostream>

using namespace std;

int main()
{
	int seed;
	MathQuiz* quiz_set[5];
	
	cout << "input seed: ";
	cin >> seed;
	RandInit(seed);
	cout << "Quiz Set #" << seed << endl << endl;
	GenerateQuizListIncDiffic(quiz_set);

	for (int j = 0; j < 5; j++)
	{
		int answer, solution;
		cout << "Q" << j + 1 << ": " << quiz_set[j]->Translate() << endl;
		cin >> answer;
		solution = quiz_set[j]->Evaluate();
		if (answer == solution)
			cout << "Correct";
		else
			cout << "Incorrect ( solution: " << solution << " )";
		cout << endl << endl;
		delete quiz_set[j];
	}

	return 0;
}