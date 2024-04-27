#include<iostream>
using namespace std;
class Admin
{

public:
	string Name;
	string Password;
	int Id;

	Admin(void);
	Admin(int, string, string);
	static void  Home();
	static void AddTeam();
	static void SetLeagueId();
	static void RemoveTeam();
	static void AddPlayer();
	static void RemovePlayer();
	static void AddRound();
	static void RemoveRound();
};

