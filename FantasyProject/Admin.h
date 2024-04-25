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
	static void RemoveTeam();
	static void AddPlayer();
};
