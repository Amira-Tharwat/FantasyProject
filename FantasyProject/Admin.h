#pragma once
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
	static void SetLeagueId();
	static void AddRound();
	static void RemoveRound();
	static void RemoveTeam();
	static void AddPlayer();
	static void RemovePlayer();
};
