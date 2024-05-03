#pragma once
#include<iostream>
using namespace std;

class Validation {

public:
	Validation();
	template <typename T>
	 T ReadNumber();

	template <typename T>
	 bool IsNumberInRange(T Number, T From, T To);


	template <typename T>
    T ReadNumberInRange(T From, T To);

};


