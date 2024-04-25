#pragma once
#include<iostream>
#include <vector>
#include<map>
#include "Team.h"
using namespace std;
static class League
{

public:
	string LaegueName;
	int LeagueId;
	static map<int,Team> teams;
	static map<int,Player> players;
	//static map<int,Round> rounds;
public:
	League();
	League(int ,string);
};

