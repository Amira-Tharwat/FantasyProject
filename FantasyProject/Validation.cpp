
#include "Validation.h"
Validation::Validation(){}
template <typename T>

T Validation::ReadNumber()
{
	T Number;
	while (!(cin >> Number)) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Invalid Number, Enter again\n";
	}
	return Number;
}

template <typename T>
bool Validation::IsNumberInRange(T Number, T From, T To)
{
	return (Number >= From && Number <= To);

}

template <typename T>
T Validation::ReadNumberInRange(T From, T To)
{
	T Number = ReadNumber<T>();

	while (!IsNumberInRange(Number, From, To))
	{
		cout << "Number is not within range, Enter again:\n";
		Number = ReadNumber<T>();
	}
	return Number;
}

