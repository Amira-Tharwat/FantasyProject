#pragma once
#include <iostream>
#include <vector>
#include "League.h"
using namespace std;
 class Admin
{
public:
	string Name;
	string Password;
	int Id;

	Admin(void);
	Admin(string, string,int);
	static void  Home();
	static void AddTeam();
	static vector<Team> RemoveV(League League, int TeamID);
	static bool FindTeamInLeague(League League,int TeamID);
	static void RemoveTeam();
	static void AddPlayer();
};
