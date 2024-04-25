#pragma once
#include <iostream>
#include <string>
#include "Team.h"
using namespace std;
class Player
{
	int CountPlayerId = 1;
public:
	int PlayerId;
	string PlayerName;
	string PlayerPosition;
	int PlayerPrice;
	Player();
	Player(int Id, string Name, string Position, int Price);
};

