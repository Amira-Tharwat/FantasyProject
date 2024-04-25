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
	int CountTeamId = 0;
public:
	string TeamName = "";
	int TeamId;
	map <int,Player> players;
	Team(void);
	Team(string, int);
	

};

