#pragma once
#include "Team.h"
#include <map>
#include <string>
using namespace std;
class League
{
public:
	string LaegueName;
	int LeagueId;
	static map<int, Team> teams;
	static map<int,Player> Players;

	//static map<int,Round> rounds;
public:
	League();
	League(int ,string);
};

