#pragma once
#include<iostream>
#include <vector>
#include<list>
#include <map>
#include<string>
#include "League.h"
#include "Player.h"
class Team
{
public:
	string TeamName = "";
	int CountTeamId = 0;
	int TeamId;
	 map <int,Player> player;
	Team(void);
	Team(string, int);
	

};

