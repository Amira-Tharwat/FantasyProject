#pragma once
#include<iostream>
#include <vector>
#include<list>
#include<string>
#include "League.h"
#include "Player.h"
class Team
{
public:
	string TeamName;
	int CountTeamId=0;
	int TeamId;
	
public:
	static list<Player> player;
	Team(void);
	Team(string, int);
	

};

