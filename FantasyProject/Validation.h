#pragma once
#include<iostream>
using namespace std;

class Validation {
public:

template <typename T>
static T ReadNumber()
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
static bool IsNumberInRange(T Number, T From, T To)
{
	return (Number >= From && Number <= To);
	
}

template <typename T>
static T ReadNumberInRange(T From, T To)
{
	T Number = ReadNumber<T>();

	while (!IsNumberInRange(Number, From, To))
	{
		cout << "Number is not within range, Enter again:\n";
		Number = ReadNumber<T>();
	}
	return Number;
}

};
