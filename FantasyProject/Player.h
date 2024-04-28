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
	map<int, int > PointsInRounds;
	Player();
	Player(int Id, string Name, string Position, int Price);
	static void setId();
};


