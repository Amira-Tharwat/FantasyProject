#pragma once
#include<iostream>
#include <vector>
#include<list>
#include<string>
#include "League.h"
//#include "Team.h"
class Player
{
public:
	int PlayerId;
	string PlayerName;
	int CountPlayerId = 0;
	string PlayerPosition;
	int PlayerPrice;
	Player();
   static void AddPlayer();

};

