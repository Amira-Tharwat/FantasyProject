#pragma once
#include<iostream>
#include<map>
using namespace std;
class Player
{

public:
	int PlayerId;
	string PlayerName;
	string PlayerPosition;
	int LeagueId;
	int TeamId;
	int PlayerPrice;
	map<int, int > PointsInRounds;
	Player();
	Player(int Id, string Name, string Position, int Price);
	
};


