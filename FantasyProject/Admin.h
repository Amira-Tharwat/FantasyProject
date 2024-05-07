#include "Leagues.h"
class Admin
{

public:
	string Name;
	string Password;
	int Id;

	Admin(void);
	Admin(int, string, string);
	static int  Home();
	static void AddTeam();
	static int SetLeagueId();
	static void RemoveTeam();
	static void AddPlayer();
	static void RemovePlayer();
	static void AddRound();
	static void clacPoints();
	static void RemoveRound();
	static void setResult();
	static void setSquadfortowteams(int,int);
};

