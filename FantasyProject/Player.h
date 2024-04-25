#pragma once
#include<iostream>
#include <vector>
#include<list>
#include<string>
#include "League.h"
//#include "Team.h"
class Player
{
	int CountPlayerId = 1;
public:
	int PlayerId;
	string PlayerName;
	string PlayerPosition;
	int PlayerPrice;
	Player();
};

