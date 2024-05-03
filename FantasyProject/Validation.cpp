
#include "Validation.h"



int Validation::ReadNumber()
{
	int Number;
	while (!(cin >> Number)) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Invalid Number, Enter again:";
	}
	return Number;
}


bool Validation::IsNumberInRange(int Number, int From, int To)
{
	return (Number >= From && Number <= To);

}


int Validation::ReadNumberInRange(int From, int To)
{
	int Number = ReadNumber();

	while (!IsNumberInRange(Number, From, To))
	{
		cout << "Number is not within range, Enter again:";
		Number = ReadNumber();
	}
	return Number;
}

