#pragma once
#include"Player.h"
#include <map>
using namespace std;

class Team
{
	int CountTeamId = 0;
public:
	string TeamName = "";
	int TeamId;
	map <int,Player> Players;
	Team(void);
	Team(string, int);
	
};

