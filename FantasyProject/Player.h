#pragma once
#include<iostream>
using namespace std;
class Player
{

public:
	int PlayerId;
	string PlayerName;
	string PlayerPosition;
	int PlayerPrice;
	Player();
	Player(int Id, string Name, string Position, int Price);
};


